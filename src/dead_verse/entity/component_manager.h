#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include "components.h"
#include "entity_manager.h"
#include "global.h"

#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>

#include "util/log.h"

namespace musashi {

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
  SparseSet() {
    // TODO: Check optimization for it instead of "resize".
    dense.reserve(kMaxComponentsSize);
    dense_to_entity.reserve(kMaxComponentsSize);
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
    auto idx = Chunk::GetChunkNumber(id);
    if (idx > entities.size()) {
      entities.resize(idx + 1);
    }
    auto idx_chunk = Chunk::GetIndexInChunk(id);

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

  ComponentManager() = default;

  Entity CreateEntity(std::string entity_name = "Entity") {
    auto id = ComponentRegistry::GenerateEntityId();
    if (id.has_value()) {
      entity_masks_.Add(id.value(), ComponentMask{});
      return Entity{id.value(), std::move(entity_name)};
    }
    kLogger->Error("Reached Entity Capacity! Quitting..");
    assert(false);
  }
  void DeleteEntity(EntityId id);

  template <IsComponent T>
  void RegisterComponent(size_t size);
  template <IsComponent T>
  void GetComponent(EntityId id);
  template <IsComponent T>
  void AddComponent(EntityId id);
  template <IsComponent T>
  void RemoveComponent(EntityId id);

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
