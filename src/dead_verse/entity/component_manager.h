#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include "components.h"
#include "entity_manager.h"
#include "global.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>

#include "util/log.h"

namespace musashi {

// Number of instances of the specific component.
static inline constexpr int kMaxComponentsSize{5000};

struct SparseSetInterface {
  virtual ~SparseSetInterface() = default;

  virtual void Delete(EntityId id) = 0;

  virtual void Clear() = 0;
  virtual size_t Size() = 0;
  virtual bool Empty() = 0;
  virtual bool Contains(EntityId id) = 0;
};

template <typename T>
struct SparseSet : public SparseSetInterface {
  explicit SparseSet(size_t size = kMaxComponentsSize) {
    // TODO: Check optimization for it instead of "resize".
    dense.reserve(size);
    dense_to_entity.reserve(size);
  }
  struct Chunk {
    // Pagination
    static constexpr uint16_t kMaxChunkSize{2048};
    static uint16_t GetChunkNumber(EntityId id) { return id / kMaxChunkSize; }
    static uint16_t GetIndexInChunk(EntityId id) { return id % kMaxChunkSize; }
  };
  using DenseIdx = EntityId;
  using SparseChunk = std::array<size_t, Chunk::kMaxChunkSize>;

  std::optional<T*> Get(EntityId id) {
    auto idx = Chunk::GetChunkNumber(id);         // Get Chunk Value
    auto idx_chunk = Chunk::GetIndexInChunk(id);  // Index In Chunk

    size_t idx_dense = entities[idx][idx_chunk];  // Index In Dense

    if (idx_dense != kNullEntity) {
      return &dense[idx_dense];
    }
    return std::nullopt;
  }

  void Add(EntityId id, T value) {
    size_t idx = Chunk::GetChunkNumber(id);
    if (idx >= entities.size()) {
      entities.resize(idx + 1);
      entities[idx].fill(kNullEntity);
    }
    auto idx_chunk = Chunk::GetIndexInChunk(id);

    // If already exists..
    if (entities[idx][idx_chunk] != kNullEntity) {
      dense[entities[idx][idx_chunk]] = std::move(value);
      dense_to_entity[entities[idx][idx_chunk]] = id;
      return;
    }

    dense.push_back(value);

    auto dense_last_idx = dense.size() - 1;
    entities[idx][idx_chunk] = dense_last_idx;

    dense_to_entity.push_back(id);
  }

  void Delete(EntityId id) override {
    auto idx = Chunk::GetChunkNumber(id);
    auto idx_chunk = Chunk::GetIndexInChunk(id);
    size_t idx_dense_delete = entities[idx][idx_chunk];

    auto idx_dense_keep = dense.size() - 1;
    auto idx_dense_to_entity_keep = dense_to_entity.back();

    std::swap(dense[idx_dense_delete], dense[idx_dense_keep]);
    std::swap(dense_to_entity[idx_dense_keep],
              dense_to_entity[idx_dense_delete]);

    auto idx_keep = Chunk::GetChunkNumber(idx_dense_to_entity_keep);
    auto idx_chunk_keep = Chunk::GetIndexInChunk(idx_dense_to_entity_keep);

    entities[idx_keep][idx_chunk_keep] = idx_dense_delete;
    entities[idx][idx_chunk] = kNullEntity;

    dense.pop_back();
    dense_to_entity.pop_back();
  }

  void Clear() override {
    dense.clear();
    entities.clear();
    dense_to_entity.clear();
  }

  size_t Size() override { return dense.size(); }

  bool Contains(EntityId id) override { return Get(id).has_value(); }

  bool Empty() override { return dense.empty(); }

  const std::vector<T>& DenseData() { return dense; }
  const std::vector<DenseIdx>& DenseToEntityData() { return dense_to_entity; }

  std::vector<T> dense;                   // Dense
  std::vector<SparseChunk> entities;      // Sparse
  std::vector<DenseIdx> dense_to_entity;  // Dense To Entity Id
};

class ComponentManager {
 public:
  using ComponentMask = std::bitset<kNumberOfComponents>;

  ComponentManager() { component_pool_.resize(kNumberOfComponents); }

  Entity CreateEntity(std::string entity_name = "Entity") {
    auto id = ComponentRegistry::GenerateEntityId();
    if (id.has_value()) {
      entity_masks_.Add(id.value(), ComponentMask{});
      return Entity{id.value(), std::move(entity_name)};
    }
    kLogger->Error("Reached Entity Capacity! Quitting..");
    assert(false);
  }

  void DeleteEntity(Entity& entity) {
    auto mask = entity_masks_.Get(entity.id);

    if (mask.has_value()) {
      for (int i = 0; i < kNumberOfComponents; ++i) {
        if (mask.value()[i] == 1) {
          component_pool_[i]->Delete(entity.id);
        }
      }
    }
    entity_masks_.Delete(entity.id);
    entity.Destroy();

    std::string log{"Entity Deleted: " + entity.name};
    kLogger->Trace(log);
  }

  template <IsComponent T>
  void RegisterComponent(size_t size = kMaxComponentsSize) {
    auto type_idx = T::Type();

    if (component_pool_.size() == kNumberOfComponents) {
      kLogger->Error("Reached Components Capacity! Quitting..");
      assert(false);
    }

    if (component_pool_[type_idx] == nullptr) {
      component_pool_[type_idx] = std::make_unique<SparseSet<T>>(size);
    }
  }

  template <IsComponent T>
  T& GetComponent(EntityId id) {
    auto type_idx = static_cast<size_t>(T::Type());

    auto& component_pool =
        *static_cast<SparseSet<T>*>(component_pool_[type_idx].get());

    auto component = component_pool.Get(id);

    if (!component.has_value()) {
      kLogger->Error("Entity Does Not Have This Component!");
      assert(false);
    }

    return *component.value();
  }

  template <IsComponent T>
  void AddComponent(EntityId id, T component) {
    auto type_idx = static_cast<size_t>(T::Type());

    auto& component_pool =
        *static_cast<SparseSet<T>*>(component_pool_[type_idx].get());

    component_pool.Add(id, std::move(component));

    auto mask = entity_masks_.Get(id);
    if (mask.has_value()) {
      mask.value()->set(type_idx);
    }
  }

  template <IsComponent T>
  void RemoveComponent(EntityId id) {
    auto type_idx = static_cast<size_t>(T::Type());

    auto& component_pool =
        *static_cast<SparseSet<T>*>(component_pool_[type_idx].get());

    component_pool.Delete(id);

    auto mask = entity_masks_.Get(id);
    if (mask.has_value()) {
      mask.value()->reset(type_idx);
    }
  }

  [[nodiscard]] size_t GetEntityCount() { return entity_masks_.Size(); }
  [[nodiscard]] size_t GetComponentPoolSize() const {
    return component_pool_.size();
  }

  void Clear() {
    entity_masks_.Clear();
    component_pool_.clear();
  }

 private:
  struct ComponentRegistry {
    static constexpr EntityId kBaseEntity{0};

    static std::optional<EntityId> GenerateEntityId() {
      static std::atomic<EntityId> next{kBaseEntity + 1};
      if (next == kMaxEntities) {
        return std::nullopt;
      }
      return next.fetch_add(1);
    }
  };

  SparseSet<ComponentMask> entity_masks_;
  std::vector<std::unique_ptr<SparseSetInterface>> component_pool_;
};

}  // namespace musashi

#endif
