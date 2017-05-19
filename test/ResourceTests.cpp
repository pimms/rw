#include <gtest/gtest.h>

#include <string>
#include <set>
#include <algorithm>

#include <core/ResourceManager.h>
#include <core/Resource.h>
#include <core/Texture.h>
#include <core/RawResource.h>

// It is assumed that the test application will be executed from the build
// directory, so g_assetDir needs to point to the testassets-directory from
// that location.
static const std::string g_assetDir = "../test/testassets";

namespace rw
{

namespace test
{

TEST(ResourceTets, InvalidRootDirThrows)
{
    ASSERT_ANY_THROW(core::ResourceManager m("./no_way_in_hell_this_dir_exists"));
}

TEST(ResourceTests, ValidRootDirDoesNotThrow)
{
    ASSERT_NO_THROW(core::ResourceManager m(g_assetDir));
}

TEST(ResourceTests, ResourceManagerInitialization)
{
    core::ResourceManager mgr(g_assetDir);

    // At the time of writing this, I'm certain that the files in the
    // testassets-directory will change over time, so I'm only going to
    // ensure that the files I *currently know* are there, are properly
    // initialized.
    //  -- J, May 15th
    const std::vector<std::string> vecassets = mgr.GetAssetList();
    ASSERT_GE(vecassets.size(), 3);

    // Copy all the items into a set to make searching slightly easier
    std::set<std::string> assets;
    std::copy(vecassets.begin(), vecassets.end(), std::inserter(assets, assets.begin()));

    // Pairing between assets, and whether or not we expect to find them in the
    // list of all assets.
    const std::vector<std::pair<std::string, bool>> expected = {
        {"bonfire.png",         true},
        {"raw.txt",             true},
        {"dir/subbonfire.png",  true},
        {".",                   false},
        {"..",                  false},
        {"dir",                 false},
        {"dir/",                false},
        {"/dir",                false},
        {"/dir/",               false},
        {"/bonfire.png",        false},
        {"/raw.txt",            false},
        {"/dir/subbonfire.png", false}
    };

    for (auto &it : expected) {
        const bool found = (assets.find(it.first) != assets.end());
        EXPECT_EQ(it.second, found) << "Asset " << it.first << " expected found: " << it.second;
    }
}

TEST(ResourceTest, GetOnEmptyHandleThrows)
{
    core::ResourceHandle handle;
    ASSERT_ANY_THROW(handle.Get());
}

TEST(ResourceTests, HandleAssignment)
{
    core::ResourceManager mgr(g_assetDir);

    core::ResourceHandle copy;

    {
        core::ResourceHandle original = mgr.Load(core::ResourceType::RAW, "raw.txt");
        ASSERT_EQ(1, original.Get()->GetRetainCount());

        // Copy the res - the copy should now also have taken ownership of the resource.
        copy = original;
        ASSERT_EQ(original.Get(), copy.Get());

        ASSERT_EQ(2, original.Get()->GetRetainCount());
        ASSERT_EQ(2, copy.Get()->GetRetainCount());
    }

    ASSERT_EQ(1, copy.Get()->GetRetainCount());

    core::ResourceHandle copy2(copy);

    ASSERT_NO_THROW(ASSERT_EQ(copy2.Get(), copy.Get()));
    ASSERT_EQ(2, copy2.Get()->GetRetainCount());
    ASSERT_EQ(2, copy.Get()->GetRetainCount());

    // Now take a "dirty" reference to the resource, and ensure that it's properly released
    core::Resource *resource = copy.Get();
    ASSERT_NE(nullptr, resource);

    copy = core::ResourceHandle();
    ASSERT_EQ(1, resource->GetRetainCount());

    copy2 = core::ResourceHandle();
    ASSERT_EQ(0, resource->GetRetainCount());

    // Ensure that purging the resource properly releases the buffer
    ASSERT_NE(0, mgr.GetLoadedBytes());
    ASSERT_NO_THROW(mgr.Purge());
    ASSERT_EQ(0, mgr.GetLoadedBytes());
}

TEST(ResourceTests, MultiAcccessOnlyLoadsOnce)
{
    core::ResourceManager mgr(g_assetDir);

    // Load the asset and record the loaded size in bytes
    core::ResourceHandle h1 = mgr.Load(core::ResourceType::RAW, "raw.txt");
    const size_t size = mgr.GetLoadedBytes();

    // After requesting the same resource again, we should not have loaded more bytes
    core::ResourceHandle h2 = mgr.Load(core::ResourceType::RAW, "raw.txt");
    ASSERT_EQ(size, mgr.GetLoadedBytes());

    // Deallocate one of them and purge the manager - we should still remain at
    // the same number of loaded bytes
    h1 = core::ResourceHandle();
    mgr.Purge();
    ASSERT_EQ(size, mgr.GetLoadedBytes());

    // Now dealloate the second handle and ensure that we're back down at 0
    h2 = core::ResourceHandle();
    mgr.Purge();
    ASSERT_EQ(0, mgr.GetLoadedBytes());
}

TEST(ResourceTests, TypeMismatchThrows)
{
    core::ResourceManager mgr(g_assetDir);

    core::ResourceHandle htex, hraw;

    // Start by just loading the texture, just to ensure that we're actually able to
    // do so.
    ASSERT_NO_THROW(htex = mgr.Load(core::ResourceType::TEXTURE, "bonfire.png"));
    htex = core::ResourceHandle();
    mgr.Purge();

    // This guy is not wrong - you are allowed to load PNGs as raw, but he's
    // being a dick for the next guy who knows it's a texture.
    ASSERT_NO_THROW(hraw = mgr.Load(core::ResourceType::RAW, "bonfire.png"));

    // Now htex will be screwed over, as the resource is bound as RAW
    ASSERT_ANY_THROW(htex = mgr.Load(core::ResourceType::TEXTURE, "bonfire.png"));
}

TEST(ResourceTests, ManagedIsCaseInsensitive)
{
    core::ResourceManager mgr(g_assetDir);

    // Ensure that if we load the same file with multiple different random
    // capitalizations, we receive the same file each time.
    core::ResourceHandle h1, h2, h3;

    h1 = mgr.Load(core::ResourceType::RAW, "raw.txt");
    ASSERT_EQ(1, h1.Get()->GetRetainCount());
    const size_t loaded = mgr.GetLoadedBytes();
    ASSERT_NE(0, loaded);

    h2 = mgr.Load(core::ResourceType::RAW, "rAW.tXt");
    ASSERT_EQ(2, h1.Get()->GetRetainCount());
    ASSERT_EQ(loaded, mgr.GetLoadedBytes());
    ASSERT_EQ(h2.Get(), h1.Get());

    h3 = mgr.Load(core::ResourceType::RAW, "RAW.txT");
    ASSERT_EQ(3, h1.Get()->GetRetainCount());
    ASSERT_EQ(loaded, mgr.GetLoadedBytes());
    ASSERT_EQ(h3.Get(), h1.Get());
}

TEST(ResourceTests, ResourcesAreProperlyLoaded)
{
    core::ResourceManager mgr(g_assetDir);

    // If this test ever fails, it's probably because you did a dumb-dumb and
    // edited the file or something.
    core::ResourceHandle raw = mgr.Load(core::ResourceType::RAW, "raw.txt");
    ASSERT_EQ("asset file\n", raw.Get<core::RawResource>()->GetAsString());
}

TEST(ResourceTests, TextureLoading)
{
    core::ResourceManager mgr(g_assetDir);
    core::ResourceHandle handle = mgr.Load(rw::core::ResourceType::TEXTURE, "bonfire.png");

    core::Resource *base = handle.Get();
    core::Texture *tex = handle.Get<core::Texture>();

    ASSERT_EQ(1, base->GetRetainCount());
    ASSERT_EQ(1, tex->GetRetainCount());
    ASSERT_EQ(core::ResourceType::TEXTURE, base->GetType());
    ASSERT_EQ(core::ResourceType::TEXTURE, tex->GetType());

    sf::Vector2u size = tex->GetSize();
    ASSERT_EQ(102, size.x);
    ASSERT_EQ(136, size.y);
}


}
}
