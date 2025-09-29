#include <FuseCore/scene/Scene.h>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

namespace {


struct TestComponent {
    int value = 0;
};

struct TestComponent2 {
    int value = 0;
};

} // namespace

TEST(Entity, ctor) {
    const fuse::Entity entity;
    EXPECT_FALSE(entity.isValid());
    EXPECT_FALSE(entity.hasComponents());
    EXPECT_FALSE(entity.hasAnyComponents());
}

TEST(Entity, destroy) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();
    EXPECT_TRUE(entity.isValid());
    EXPECT_TRUE(entity);
    EXPECT_TRUE(entity.hasComponents());

    entity.destroy();
    EXPECT_FALSE(entity.isValid());
    EXPECT_FALSE(entity);
    EXPECT_FALSE(entity.hasComponents());
}

TEST(Entity, addComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    auto comp1 = entity.addComponent<TestComponent>(10);
    auto comp2 = entity.addComponent<TestComponent2>(20);
    EXPECT_EQ(comp1.value, 10);
    EXPECT_EQ(comp2.value, 20);

    EXPECT_TRUE(entity.hasComponents<TestComponent>());
    EXPECT_TRUE(entity.hasComponents<TestComponent2>());
    EXPECT_TRUE((entity.hasComponents<TestComponent, TestComponent2>()));
}

TEST(Entity, addOrReplaceComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    auto& compRef1 = entity.addOrReplaceComponent<TestComponent>(10);
    EXPECT_EQ(compRef1.value, 10);

    auto& compRef2 = entity.addOrReplaceComponent<TestComponent>(20);
    EXPECT_EQ(compRef1.value, 20);
    EXPECT_EQ(compRef2.value, 20);
}

TEST(Entity, patchComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    auto& comp = entity.addComponent<TestComponent>(10);
    EXPECT_EQ(comp.value, 10);

    // no callback (nothing change)
    entity.patchComponent<TestComponent>();
    EXPECT_EQ(comp.value, 10);

    // 1 callback
    entity.patchComponent<TestComponent>([](TestComponent& comp) { comp.value = 20; });
    EXPECT_EQ(comp.value, 20);

    // multi callback
    entity.patchComponent<TestComponent>([](TestComponent& comp) { comp.value = 30; },
                                         [](TestComponent& comp) { comp.value = 40; });
    EXPECT_EQ(comp.value, 40);
}

TEST(Entity, replaceComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    auto& comp = entity.addComponent<TestComponent>(10);
    EXPECT_EQ(comp.value, 10);

    // replace with no args
    auto& comp2 = entity.replaceComponent<TestComponent>();
    EXPECT_EQ(comp2.value, 0);
    EXPECT_EQ(comp2.value, comp.value);

    // replace with no args ... nothing change
    auto& comp3 = entity.replaceComponent<TestComponent>(20);
    EXPECT_EQ(comp3.value, 20);
    EXPECT_EQ(comp3.value, comp.value);
}

TEST(Entity, removeComponents) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    // try removing non existing components.
    EXPECT_EQ(entity.removeComponents<TestComponent>(), 0);
    EXPECT_EQ((entity.removeComponents<TestComponent, TestComponent2>()), 0);

    // removing 1 existing components.
    entity.addComponent<TestComponent>(10);
    EXPECT_EQ(entity.removeComponents<TestComponent>(), 1);
    EXPECT_FALSE(entity.hasComponents<TestComponent>());

    // removing 1 existing components and 1 non existing component.
    entity.addComponent<TestComponent>(20);
    EXPECT_EQ((entity.removeComponents<TestComponent, TestComponent2>()), 1);
    EXPECT_FALSE(entity.hasComponents<TestComponent>());

    // removing 2 existing components.
    entity.addComponent<TestComponent>(20);
    entity.addComponent<TestComponent2>(20);
    EXPECT_TRUE((entity.hasComponents<TestComponent, TestComponent2>()));
    EXPECT_EQ((entity.removeComponents<TestComponent, TestComponent2>()), 2);
    EXPECT_FALSE((entity.hasComponents<TestComponent, TestComponent2>()));
}

TEST(Entity, eraseComponents) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    // removing 1 existing components.
    entity.addComponent<TestComponent>(10);
    entity.eraseComponents<TestComponent>();
    EXPECT_FALSE(entity.hasComponents<TestComponent>());

    // removing 2 existing components.
    entity.addComponent<TestComponent>(20);
    entity.addComponent<TestComponent2>(20);
    EXPECT_TRUE((entity.hasComponents<TestComponent, TestComponent2>()));
    entity.eraseComponents<TestComponent, TestComponent2>();
    EXPECT_FALSE((entity.hasComponents<TestComponent, TestComponent2>()));
}

TEST(Entity, getComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    // get 1 existing components.
    entity.addComponent<TestComponent>(10);
    EXPECT_EQ(entity.getComponent<TestComponent>().value, 10);
    entity.getComponent<TestComponent>().value = 20;
    EXPECT_EQ(entity.getComponent<TestComponent>().value, 20);


    // get multi existing components.
    entity.addComponent<TestComponent2>(200);
    {
        auto [comp1, comp2] = entity.getComponent<TestComponent, TestComponent2>();
        EXPECT_EQ(comp1.value, 20);
        EXPECT_EQ(comp2.value, 200);
        comp1.value = 40;
        comp2.value = 50;
    }

    auto [comp1, comp2] = entity.getComponent<TestComponent, TestComponent2>();
    EXPECT_EQ(comp1.value, 40);
    EXPECT_EQ(comp2.value, 50);
}

TEST(Entity, getOrAddComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    EXPECT_EQ(entity.getOrAddComponent<TestComponent>(10).value, 10); // this will create it
    entity.getOrAddComponent<TestComponent>(10).value = 20; // this will get is (param is ignored)
    EXPECT_EQ(entity.getOrAddComponent<TestComponent>(10).value,
              20); // this will get is (param is ignored
}

TEST(Entity, tryGetComponent) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    // try to get non existing component
    {
        EXPECT_EQ(entity.tryGetComponent<TestComponent>(), nullptr);
        auto [comp1, comp2] = entity.tryGetComponent<TestComponent, TestComponent2>();
        EXPECT_EQ(comp1, nullptr);
        EXPECT_EQ(comp2, nullptr);
    }

    // try to get 1 existing component  and 1 non existing component
    {
        entity.addComponent<TestComponent>();
        EXPECT_NE(entity.tryGetComponent<TestComponent>(), nullptr);
        auto [comp1, comp2] = entity.tryGetComponent<TestComponent, TestComponent2>();
        EXPECT_NE(comp1, nullptr);
        EXPECT_EQ(comp2, nullptr);
    }

    // try to get 2 existing components
    {
        entity.addComponent<TestComponent2>();
        EXPECT_NE(entity.tryGetComponent<TestComponent>(), nullptr);
        EXPECT_NE(entity.tryGetComponent<TestComponent2>(), nullptr);
        auto [comp1, comp2] = entity.tryGetComponent<TestComponent, TestComponent2>();
        EXPECT_NE(comp1, nullptr);
        EXPECT_NE(comp2, nullptr);
    }
}

TEST(Entity, hasComponents) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    EXPECT_FALSE(entity.hasComponents<TestComponent>());
    entity.addComponent<TestComponent>();
    EXPECT_TRUE(entity.hasComponents<TestComponent>());

    EXPECT_FALSE(entity.hasComponents<TestComponent2>());
    EXPECT_FALSE((entity.hasComponents<TestComponent, TestComponent2>()));

    entity.addComponent<TestComponent2>();
    EXPECT_TRUE(entity.hasComponents<TestComponent2>());
    EXPECT_TRUE((entity.hasComponents<TestComponent, TestComponent2>()));
}

TEST(Entity, hasAnyComponents) {
    fuse::Scene  scene;
    fuse::Entity entity = scene.createEntity();

    EXPECT_FALSE(entity.hasAnyComponents());
    EXPECT_FALSE(entity.hasAnyComponents<TestComponent>());
    EXPECT_FALSE((entity.hasAnyComponents<TestComponent, TestComponent2>()));

    entity.addComponent<TestComponent>();
    EXPECT_FALSE(entity.hasAnyComponents());
    EXPECT_TRUE(entity.hasAnyComponents<TestComponent>());
    EXPECT_FALSE(entity.hasAnyComponents<TestComponent2>());
    EXPECT_TRUE((entity.hasAnyComponents<TestComponent, TestComponent2>()));

    entity.addComponent<TestComponent2>();
    EXPECT_FALSE(entity.hasAnyComponents());
    EXPECT_TRUE(entity.hasAnyComponents<TestComponent>());
    EXPECT_TRUE(entity.hasAnyComponents<TestComponent2>());
    EXPECT_TRUE((entity.hasAnyComponents<TestComponent, TestComponent2>()));
}
