#include <FuseCore/scene/Scene.h>

#include <gtest/gtest.h>

#include <print>

namespace {

    struct TestComponent {
    int value = 0;
};

} // namespace

TEST(Scene, ctor) {
    const fuse::Scene scene;
    EXPECT_TRUE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 0);
}

TEST(Scene, createEntity) {
    fuse::Scene scene;

    // create some entities
    std::ignore = scene.createEntity();
    std::ignore = scene.createEntity();
    std::ignore = scene.createEntity();
    EXPECT_FALSE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 3);

    // clear the scene
    scene.clear();
    EXPECT_TRUE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 0);

    // recreate some entities
    std::ignore = scene.createEntity();
    std::ignore = scene.createEntity();
    std::ignore = scene.createEntity();
    EXPECT_FALSE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 3);
}

TEST(Scene, destroyEntity) {
    fuse::Scene scene;

    // create some entities
    auto entity1 = scene.createEntity();
    auto entity2 = scene.createEntity();
    auto entity3 = scene.createEntity();
    EXPECT_FALSE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 3);

    // remove all entity
    scene.destroyEntity(entity1);
    scene.destroyEntity(entity2);
    scene.destroyEntity(entity3);

    EXPECT_EQ(entity1, fuse::Entity());
    EXPECT_EQ(entity2, fuse::Entity());
    EXPECT_EQ(entity3, fuse::Entity());

    EXPECT_TRUE(scene.isEmpty());
    EXPECT_EQ(scene.getEntityCount(), 0);
}

TEST(Scene, hasSameComponentType) {
    fuse::Scene scene;
    auto        entity1 = scene.createEntity();
    auto        entity2 = scene.createEntity();

    EXPECT_TRUE(scene.hasSameComponentType(entity1, entity2));

    entity1.addComponent<TestComponent>(10);
    EXPECT_FALSE(scene.hasSameComponentType(entity1, entity2));

    entity2.addComponent<TestComponent>(20);
    EXPECT_TRUE(scene.hasSameComponentType(entity1, entity2));

    entity2.eraseComponents<TestComponent>();
    EXPECT_FALSE(scene.hasSameComponentType(entity1, entity2));

    entity1.eraseComponents<TestComponent>();
    EXPECT_TRUE(scene.hasSameComponentType(entity1, entity2));
}

TEST(Scene, duplicateEntity) {
    fuse::Scene scene;

    auto entity1 = scene.createEntity();
    ASSERT_EQ(scene.getEntityComponentCount(entity1), 2);
    ASSERT_TRUE(entity1.hasComponents<fuse::NameComponent>());
    ASSERT_TRUE(entity1.hasComponents<fuse::IDComponent>());

    // the duplicated entity should have the same component as the other entity.
    auto entity2 = scene.duplicateEntity(entity1);
    ASSERT_EQ(scene.getEntityComponentCount(entity2), 2);

    ASSERT_TRUE(scene.hasSameComponentType(entity1, entity2));

    ASSERT_TRUE(entity2.hasComponents<fuse::NameComponent>());
    ASSERT_TRUE(entity2.hasComponents<fuse::IDComponent>());

    // both entity should have the same name
    ASSERT_EQ(entity1.getComponent<fuse::NameComponent>(),
              entity2.getComponent<fuse::NameComponent>());

    // component ID should be different
    ASSERT_NE(entity1.getComponent<fuse::IDComponent>(), entity2.getComponent<fuse::IDComponent>());
}
