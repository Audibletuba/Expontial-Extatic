#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include "ResourceManager.h"
#include "Sprite.h"
#include "Frame.h"
#include "Sound.h"
#include "Music.h"
#include "Box.h"
#include "Object.h"
#include "WorldManager.h"
#include "Animation.h"
#include "Color.h"

bool check(bool condition, const std::string& test_name)
{
    if (condition)
    {
        std::cout << "PASS: " << test_name << std::endl;
        return true;
    }

    std::cout << "FAIL: " << test_name << std::endl;
    return false;
}

bool sameVector(Vector a, Vector b)
{
    return a.getX() == b.getX() &&
        a.getY() == b.getY();
}

bool containsObject(ObjectList list, Object* object)
{
    for (int i = 0; i < list.getCount(); i++)
    {
        if (list[i] == object)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int failures = 0;

    ResourceManager& rm =
        ResourceManager::getInstance();

    WorldManager& wm =
        WorldManager::getInstance();

    std::cout << "========================================"
        << std::endl;
    std::cout << "2C TEST SUITE"
        << std::endl;
    std::cout << "BASE + EDGE + ERROR CASES"
        << std::endl;
    std::cout << "========================================"
        << std::endl;

    // ============================================================
    // STARTUP
    // ============================================================

    if (!check(
        rm.startUp() == 0,
        "ResourceManager startup"))
    {
        failures++;
    }

    wm.startUp();

    // ============================================================
    // BASE FUNCTIONAL TESTS
    // ============================================================

    std::cout << "\n========================================"
        << std::endl;
    std::cout << "BASE FUNCTIONAL TESTS"
        << std::endl;
    std::cout << "========================================"
        << std::endl;

    // ------------------------------------------------------------
    // Frame
    // ------------------------------------------------------------

    std::cout << "\n--- Frame Tests ---" << std::endl;

    Frame frame;

    frame.setWidth(3);
    frame.setHeight(2);
    frame.setString("ABCDEF");

    if (!check(
        frame.getWidth() == 3,
        "Frame width"))
    {
        failures++;
    }

    if (!check(
        frame.getHeight() == 2,
        "Frame height"))
    {
        failures++;
    }

    if (!check(
        frame.getString() == "ABCDEF",
        "Frame data"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Box
    // ------------------------------------------------------------

    std::cout << "\n--- Box Tests ---" << std::endl;

    Box box(Vector(10, 20), 5, 3);

    if (!check(
        sameVector(
            box.getCorner(),
            Vector(10, 20)),
        "Box corner"))
    {
        failures++;
    }

    if (!check(
        box.getHorizontal() == 5,
        "Box horizontal dimension"))
    {
        failures++;
    }

    if (!check(
        box.getVertical() == 3,
        "Box vertical dimension"))
    {
        failures++;
    }

    box.setCorner(Vector(2, 4));
    box.setHorizontal(8);
    box.setVertical(6);

    if (!check(
        sameVector(
            box.getCorner(),
            Vector(2, 4)),
        "Box setCorner()"))
    {
        failures++;
    }

    if (!check(
        box.getHorizontal() == 8,
        "Box setHorizontal()"))
    {
        failures++;
    }

    if (!check(
        box.getVertical() == 6,
        "Box setVertical()"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Sprite Resource
    // ------------------------------------------------------------

    std::cout << "\n--- Sprite Resource Tests ---"
        << std::endl;

    if (!check(
        rm.loadSprite(
            "Sprites/test_sprite.txt",
            "test-sprite") == 0,
        "loadSprite() succeeds"))
    {
        failures++;
    }

    Sprite* sprite =
        rm.getSprite("test-sprite");

    if (!check(
        sprite != nullptr,
        "getSprite() finds loaded Sprite"))
    {
        failures++;
    }

    if (sprite != nullptr)
    {
        if (!check(
            sprite->getLabel() == "test-sprite",
            "Loaded Sprite label"))
        {
            failures++;
        }

        if (!check(
            sprite->getWidth() == 5,
            "Loaded Sprite width"))
        {
            failures++;
        }

        if (!check(
            sprite->getHeight() == 3,
            "Loaded Sprite height"))
        {
            failures++;
        }

        if (!check(
            sprite->getSlowdown() == 1,
            "Loaded Sprite slowdown"))
        {
            failures++;
        }

        if (!check(
            sprite->getColor() == YELLOW,
            "Loaded Sprite color"))
        {
            failures++;
        }

        if (!check(
            sprite->getFrameCount() == 2,
            "Loaded Sprite frame count"))
        {
            failures++;
        }

        Frame sprite_frame0 =
            sprite->getFrame(0);

        if (!check(
            sprite_frame0.getWidth() == 5 &&
            sprite_frame0.getHeight() == 3 &&
            sprite_frame0.getString() ==
            "  A  "
            " AAA "
            "A   A",
            "Loaded Sprite frame 0 data"))
        {
            failures++;
        }

        Frame sprite_frame1 =
            sprite->getFrame(1);

        if (!check(
            sprite_frame1.getWidth() == 5 &&
            sprite_frame1.getHeight() == 3 &&
            sprite_frame1.getString() ==
            "  B  "
            " BBB "
            "B   B",
            "Loaded Sprite frame 1 data"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Sound
    // ------------------------------------------------------------

    std::cout << "\n--- Sound Tests ---" << std::endl;

    if (!check(
        rm.loadSound(
            "Sounds/fire.wav",
            "fire") == 0,
        "loadSound() succeeds"))
    {
        failures++;
    }

    Sound* sound =
        rm.getSound("fire");

    if (!check(
        sound != nullptr,
        "getSound() finds loaded Sound"))
    {
        failures++;
    }

    if (sound != nullptr)
    {
        if (!check(
            sound->getLabel() == "fire",
            "Loaded Sound label"))
        {
            failures++;
        }

        sound->play();

        if (!check(
            true,
            "Sound play() does not crash"))
        {
            failures++;
        }

        sound->stop();

        if (!check(
            true,
            "Sound stop() does not crash"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Music
    // ------------------------------------------------------------

    std::cout << "\n--- Music Tests ---" << std::endl;

    if (!check(
        rm.loadMusic(
            "Sounds/start-music.wav",
            "start-music") == 0,
        "loadMusic() succeeds"))
    {
        failures++;
    }

    Music* music =
        rm.getMusic("start-music");

    if (!check(
        music != nullptr,
        "getMusic() finds loaded Music"))
    {
        failures++;
    }

    if (music != nullptr)
    {
        if (!check(
            music->getLabel() == "start-music",
            "Loaded Music label"))
        {
            failures++;
        }

        music->play();

        if (!check(
            true,
            "Music play() does not crash"))
        {
            failures++;
        }

        music->stop();

        if (!check(
            true,
            "Music stop() does not crash"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Object + Sprite
    // ------------------------------------------------------------

    std::cout << "\n--- Object + Sprite Tests ---"
        << std::endl;

    Object object(Vector(20, 20));

    if (!check(
        object.setSprite("test-sprite") == 0,
        "Object setSprite() succeeds"))
    {
        failures++;
    }

    Animation animation =
        object.getAnimation();

    Sprite* object_sprite =
        animation.getSprite();

    if (!check(
        sprite != nullptr &&
        object_sprite != nullptr &&
        object_sprite == sprite,
        "Object animation uses loaded Sprite"))
    {
        failures++;
    }

    Box object_box =
        object.getBox();

    if (!check(
        object_box.getHorizontal() == 5 &&
        object_box.getVertical() == 3,
        "Object bounding box matches Sprite size"))
    {
        failures++;
    }

    if (!check(
        sameVector(
            object_box.getCorner(),
            Vector(-2.5f, -1.5f)),
        "Object bounding box is centered on Object"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Animation
    // ------------------------------------------------------------

    std::cout << "\n--- Animation Tests ---"
        << std::endl;

    Animation object_animation =
        object.getAnimation();

    if (!check(
        object_animation.getSprite() != nullptr &&
        object_animation.getSprite() == sprite,
        "Animation has correct Sprite"))
    {
        failures++;
    }

    if (!check(
        object_animation.getIndex() == 0,
        "Animation starts at frame 0"))
    {
        failures++;
    }

    object_animation.draw(
        object.getPosition());

    if (!check(
        object_animation.getIndex() == 1,
        "Animation advances according to slowdown"))
    {
        failures++;
    }

    object_animation.draw(
        object.getPosition());

    if (!check(
        object_animation.getIndex() == 0,
        "Animation loops back to frame 0"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // WorldManager collision
    // ------------------------------------------------------------

    std::cout << "\n--- WorldManager Collision Tests ---"
        << std::endl;

    Object object1(Vector(10, 10));
    Object object2(Vector(13, 10));

    if (!check(
        object1.setSprite("test-sprite") == 0,
        "Object 1 receives Sprite"))
    {
        failures++;
    }

    if (!check(
        object2.setSprite("test-sprite") == 0,
        "Object 2 receives Sprite"))
    {
        failures++;
    }

    wm.addObject(&object1);
    wm.addObject(&object2);

    ObjectList collisions =
        wm.getCollisions(
            &object1,
            object1.getPosition());

    if (!check(
        containsObject(
            collisions,
            &object2),
        "Large Sprite bounding boxes detect collision"))
    {
        failures++;
    }

    Box box1 =
        object1.getBox();

    Box box2 =
        object2.getBox();

    if (!check(
        box1.getHorizontal() == 5 &&
        box1.getVertical() == 3 &&
        box2.getHorizontal() == 5 &&
        box2.getVertical() == 3,
        "Collision objects have Sprite-sized boxes"))
    {
        failures++;
    }

    // ============================================================
    // EDGE-CASE TESTS
    // ============================================================

    std::cout << "\n========================================"
        << std::endl;
    std::cout << "EDGE-CASE TESTS"
        << std::endl;
    std::cout << "========================================"
        << std::endl;

    // ------------------------------------------------------------
    // 1x1 Frame
    // ------------------------------------------------------------

    std::cout << "\n--- Smallest Valid Frame ---"
        << std::endl;

    Frame tiny_frame;

    tiny_frame.setWidth(1);
    tiny_frame.setHeight(1);
    tiny_frame.setString("X");

    if (!check(
        tiny_frame.getWidth() == 1 &&
        tiny_frame.getHeight() == 1 &&
        tiny_frame.getString() == "X",
        "1x1 Frame stores correctly"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid frame indexes
    // ------------------------------------------------------------

    std::cout << "\n--- Frame Index Boundaries ---"
        << std::endl;

    if (sprite != nullptr)
    {
        Frame negative_frame =
            sprite->getFrame(-1);

        Frame past_end_frame =
            sprite->getFrame(
                sprite->getFrameCount());

        if (!check(
            negative_frame.getString() == "",
            "Negative frame index is rejected"))
        {
            failures++;
        }

        if (!check(
            past_end_frame.getString() == "",
            "Frame index past frame count is rejected"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Object at origin
    // ------------------------------------------------------------

    std::cout << "\n--- Object at Origin ---"
        << std::endl;

    Object origin_object(Vector(0, 0));

    if (!check(
        origin_object.setSprite("test-sprite") == 0,
        "Object at origin accepts Sprite"))
    {
        failures++;
    }

    Box origin_box =
        origin_object.getBox();

    if (!check(
        sameVector(
            origin_box.getCorner(),
            Vector(-2.5f, -1.5f)),
        "Sprite bounding box is centered at Object origin"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // 1-frame / 1x1 Sprite
    // ------------------------------------------------------------

    std::cout << "\n--- 1x1 Sprite Boundary ---"
        << std::endl;

    std::ofstream edge_file(
        "edge_sprite.txt");

    edge_file
        << "1\n"
        << "1\n"
        << "1\n"
        << "1\n"
        << "white\n"
        << "X\n";

    edge_file.close();

    if (!check(
        rm.loadSprite(
            "edge_sprite.txt",
            "edge-sprite") == 0,
        "1-frame 1x1 Sprite loads"))
    {
        failures++;
    }

    Sprite* edge_sprite =
        rm.getSprite("edge-sprite");

    if (!check(
        edge_sprite != nullptr,
        "1x1 Sprite can be retrieved"))
    {
        failures++;
    }

    if (edge_sprite != nullptr)
    {
        if (!check(
            edge_sprite->getWidth() == 1 &&
            edge_sprite->getHeight() == 1,
            "1x1 Sprite has correct dimensions"))
        {
            failures++;
        }

        if (!check(
            edge_sprite->getFrameCount() == 1,
            "1x1 Sprite has exactly one frame"))
        {
            failures++;
        }

        Animation edge_animation;

        edge_animation.setSprite(
            edge_sprite);

        edge_animation.draw(
            Vector(0, 0));

        if (!check(
            edge_animation.getIndex() == 0,
            "1-frame animation remains on frame 0"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Exact Sprite frame capacity
    // ------------------------------------------------------------

    std::cout << "\n--- Exact Frame Capacity ---"
        << std::endl;

    Sprite capacity_sprite(3);

    Frame capacity_frame;

    capacity_frame.setWidth(1);
    capacity_frame.setHeight(1);
    capacity_frame.setString("X");

    if (!check(
        capacity_sprite.addFrame(
            capacity_frame) == 0,
        "Frame 1 fits within Sprite capacity"))
    {
        failures++;
    }

    if (!check(
        capacity_sprite.addFrame(
            capacity_frame) == 0,
        "Frame 2 fits within Sprite capacity"))
    {
        failures++;
    }

    if (!check(
        capacity_sprite.addFrame(
            capacity_frame) == 0,
        "Frame 3 fits exactly at Sprite capacity"))
    {
        failures++;
    }

    if (!check(
        capacity_sprite.getFrameCount() == 3,
        "Sprite contains exactly its maximum frame count"))
    {
        failures++;
    }

    if (!check(
        capacity_sprite.addFrame(
            capacity_frame) == -1,
        "Frame beyond Sprite capacity is rejected"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Slowdown = 1
    // ------------------------------------------------------------

    std::cout << "\n--- Slowdown = 1 ---"
        << std::endl;

    Animation slowdown_one =
        object.getAnimation();

    slowdown_one.setIndex(0);
    slowdown_one.setSlowdownCount(0);

    slowdown_one.draw(
        Vector(0, 0));

    if (!check(
        slowdown_one.getIndex() == 1,
        "Slowdown 1 advances after first draw"))
    {
        failures++;
    }

    slowdown_one.draw(
        Vector(0, 0));

    if (!check(
        slowdown_one.getIndex() == 0,
        "Slowdown 1 advances every draw"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Slowdown = 2
    // ------------------------------------------------------------

    std::cout << "\n--- Slowdown = 2 ---"
        << std::endl;

    std::ofstream slowdown_file(
        "slowdown_two.txt");

    slowdown_file
        << "2\n"
        << "1\n"
        << "1\n"
        << "2\n"
        << "white\n"
        << "A\n"
        << "B\n";

    slowdown_file.close();

    if (!check(
        rm.loadSprite(
            "slowdown_two.txt",
            "slowdown-two") == 0,
        "Slowdown 2 Sprite loads"))
    {
        failures++;
    }

    Sprite* slowdown_sprite =
        rm.getSprite("slowdown-two");

    if (!check(
        slowdown_sprite != nullptr &&
        slowdown_sprite->getSlowdown() == 2,
        "Slowdown 2 value is stored"))
    {
        failures++;
    }

    if (slowdown_sprite != nullptr)
    {
        Animation slowdown_two;

        slowdown_two.setSprite(
            slowdown_sprite);

        if (!check(
            slowdown_two.getIndex() == 0,
            "Slowdown 2 starts at frame 0"))
        {
            failures++;
        }

        slowdown_two.draw(
            Vector(0, 0));

        if (!check(
            slowdown_two.getIndex() == 0,
            "Slowdown 2 does not advance on first draw"))
        {
            failures++;
        }

        slowdown_two.draw(
            Vector(0, 0));

        if (!check(
            slowdown_two.getIndex() == 1,
            "Slowdown 2 advances on second draw"))
        {
            failures++;
        }

        slowdown_two.draw(
            Vector(0, 0));

        if (!check(
            slowdown_two.getIndex() == 1,
            "Slowdown 2 remains on frame for one draw"))
        {
            failures++;
        }

        slowdown_two.draw(
            Vector(0, 0));

        if (!check(
            slowdown_two.getIndex() == 0,
            "Slowdown 2 loops after correct number of draws"))
        {
            failures++;
        }
    }

    // ------------------------------------------------------------
    // Stopped animation
    // ------------------------------------------------------------

    std::cout << "\n--- Stopped Animation ---"
        << std::endl;

    Animation stopped_animation =
        object.getAnimation();

    stopped_animation.setIndex(0);
    stopped_animation.setSlowdownCount(-1);

    stopped_animation.draw(Vector(0, 0));
    stopped_animation.draw(Vector(0, 0));
    stopped_animation.draw(Vector(0, 0));

    if (!check(
        stopped_animation.getIndex() == 0,
        "Negative slowdown count keeps animation stopped"))
    {
        failures++;
    }

    if (!check(
        stopped_animation.getSlowdownCount() == -1,
        "Stopped animation preserves slowdown count"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Altitude boundaries
    // ------------------------------------------------------------

    std::cout << "\n--- Altitude Boundaries ---"
        << std::endl;

    Object altitude_object(
        Vector(0, 0));

    if (!check(
        altitude_object.setAltitude(0) == 0,
        "Minimum altitude is accepted"))
    {
        failures++;
    }

    if (!check(
        altitude_object.setAltitude(
            MAX_ALTITUDE) == 0,
        "Maximum altitude is accepted"))
    {
        failures++;
    }

    if (!check(
        altitude_object.setAltitude(-1) == -1,
        "Altitude below minimum is rejected"))
    {
        failures++;
    }

    if (!check(
        altitude_object.setAltitude(
            MAX_ALTITUDE + 1) == -1,
        "Altitude above maximum is rejected"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Separated boxes
    // ------------------------------------------------------------

    std::cout << "\n--- Separated Boxes ---"
        << std::endl;

    Object separated1(Vector(0, 0));
    Object separated2(Vector(20, 0));

    separated1.setSprite("test-sprite");
    separated2.setSprite("test-sprite");

    wm.addObject(&separated1);
    wm.addObject(&separated2);

    ObjectList separated_collisions =
        wm.getCollisions(
            &separated1,
            separated1.getPosition());

    if (!check(
        !containsObject(
            separated_collisions,
            &separated2),
        "Separated boxes do not collide"))
    {
        failures++;
    }

    wm.removeObject(&separated1);
    wm.removeObject(&separated2);

    // ------------------------------------------------------------
    // Partial overlap
    // ------------------------------------------------------------

    std::cout << "\n--- Partial Overlap ---"
        << std::endl;

    Object overlap1(Vector(0, 0));
    Object overlap2(Vector(3, 0));

    overlap1.setSprite("test-sprite");
    overlap2.setSprite("test-sprite");

    wm.addObject(&overlap1);
    wm.addObject(&overlap2);

    ObjectList overlap_collisions =
        wm.getCollisions(
            &overlap1,
            overlap1.getPosition());

    if (!check(
        containsObject(
            overlap_collisions,
            &overlap2),
        "Partially overlapping boxes collide"))
    {
        failures++;
    }

    wm.removeObject(&overlap1);
    wm.removeObject(&overlap2);

    // ------------------------------------------------------------
    // Box completely inside another
    // ------------------------------------------------------------

    std::cout << "\n--- Contained Box ---"
        << std::endl;

    Object large_object(Vector(0, 0));
    Object small_object(Vector(0, 0));

    large_object.setSprite("test-sprite");
    small_object.setSprite("edge-sprite");

    wm.addObject(&large_object);
    wm.addObject(&small_object);

    ObjectList inside_collisions =
        wm.getCollisions(
            &large_object,
            large_object.getPosition());

    if (!check(
        containsObject(
            inside_collisions,
            &small_object),
        "Box completely inside another detects collision"))
    {
        failures++;
    }

    wm.removeObject(&large_object);
    wm.removeObject(&small_object);

    // ------------------------------------------------------------
    // Edge touching
    // ------------------------------------------------------------

    std::cout << "\n--- Edge Touching ---"
        << std::endl;

    Object touching1(Vector(0, 0));
    Object touching2(Vector(5, 0));

    touching1.setSprite("test-sprite");
    touching2.setSprite("test-sprite");

    wm.addObject(&touching1);
    wm.addObject(&touching2);

    ObjectList touching_collisions =
        wm.getCollisions(
            &touching1,
            touching1.getPosition());

    if (!check(
        containsObject(
            touching_collisions,
            &touching2),
        "Boxes touching at edge count as collision"))
    {
        failures++;
    }

    wm.removeObject(&touching1);
    wm.removeObject(&touching2);

    // ------------------------------------------------------------
    // Non-solid object
    // ------------------------------------------------------------

    std::cout << "\n--- Non-Solid Object ---"
        << std::endl;

    Object solid_object(Vector(0, 0));
    Object spectral_object(Vector(0, 0));

    solid_object.setSprite("test-sprite");
    spectral_object.setSprite("test-sprite");

    spectral_object.setSolidness(SPECTRAL);

    wm.addObject(&solid_object);
    wm.addObject(&spectral_object);

    ObjectList spectral_collisions =
        wm.getCollisions(
            &solid_object,
            solid_object.getPosition());

    if (!check(
        !containsObject(
            spectral_collisions,
            &spectral_object),
        "Non-solid object is ignored by collision detection"))
    {
        failures++;
    }

    wm.removeObject(&solid_object);
    wm.removeObject(&spectral_object);

    // ------------------------------------------------------------
    // Self collision
    // ------------------------------------------------------------

    std::cout << "\n--- Self Collision ---"
        << std::endl;

    Object self_object(Vector(0, 0));

    self_object.setSprite("test-sprite");

    wm.addObject(&self_object);

    ObjectList self_collisions =
        wm.getCollisions(
            &self_object,
            self_object.getPosition());

    if (!check(
        !containsObject(
            self_collisions,
            &self_object),
        "Object does not collide with itself"))
    {
        failures++;
    }

    wm.removeObject(&self_object);

    // ------------------------------------------------------------
    // Default box vs Sprite-sized box
    // ------------------------------------------------------------

    std::cout << "\n--- Default Box vs Sprite Box ---"
        << std::endl;

    Object default_box1(Vector(0, 0));
    Object default_box2(Vector(2, 0));

    wm.addObject(&default_box1);
    wm.addObject(&default_box2);

    ObjectList default_collisions =
        wm.getCollisions(
            &default_box1,
            default_box1.getPosition());

    if (!check(
        !containsObject(
            default_collisions,
            &default_box2),
        "Default boxes at separated positions do not collide"))
    {
        failures++;
    }

    default_box1.setSprite("test-sprite");
    default_box2.setSprite("test-sprite");

    ObjectList sprite_collisions =
        wm.getCollisions(
            &default_box1,
            default_box1.getPosition());

    if (!check(
        containsObject(
            sprite_collisions,
            &default_box2),
        "Sprite-sized boxes collide"))
    {
        failures++;
    }

    wm.removeObject(&default_box1);
    wm.removeObject(&default_box2);

    // ============================================================
    // ERROR-CASE TESTS
    // ============================================================

    std::cout << "\n========================================"
        << std::endl;
    std::cout << "ERROR-CASE TESTS"
        << std::endl;
    std::cout << "========================================"
        << std::endl;

    // ------------------------------------------------------------
    // Unknown resource lookups
    // ------------------------------------------------------------

    std::cout << "\n--- Resource Lookup Errors ---"
        << std::endl;

    if (!check(
        rm.getSprite("does-not-exist") == nullptr,
        "getSprite() returns nullptr for unknown label"))
    {
        failures++;
    }

    if (!check(
        rm.getSound("does-not-exist") == nullptr,
        "getSound() returns nullptr for unknown label"))
    {
        failures++;
    }

    if (!check(
        rm.getMusic("does-not-exist") == nullptr,
        "getMusic() returns nullptr for unknown label"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Unload nonexistent resources
    // ------------------------------------------------------------

    std::cout << "\n--- Resource Unload Errors ---"
        << std::endl;

    if (!check(
        rm.unloadSprite("does-not-exist") == -1,
        "unloadSprite() rejects unknown label"))
    {
        failures++;
    }

    if (!check(
        rm.unloadSound("does-not-exist") == -1,
        "unloadSound() rejects unknown label"))
    {
        failures++;
    }

    if (!check(
        rm.unloadMusic("does-not-exist") == -1,
        "unloadMusic() rejects unknown label"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Double unload
    // ------------------------------------------------------------

    std::cout << "\n--- Double Unload Errors ---"
        << std::endl;

    if (!check(
        rm.unloadSprite("edge-sprite") == 0,
        "First unload of Sprite succeeds"))
    {
        failures++;
    }

    if (!check(
        rm.unloadSprite("edge-sprite") == -1,
        "Second unload of Sprite fails gracefully"))
    {
        failures++;
    }

    if (!check(
        rm.unloadSound("fire") == 0,
        "First unload of Sound succeeds"))
    {
        failures++;
    }

    if (!check(
        rm.unloadSound("fire") == -1,
        "Second unload of Sound fails gracefully"))
    {
        failures++;
    }

    if (!check(
        rm.unloadMusic("start-music") == 0,
        "First unload of Music succeeds"))
    {
        failures++;
    }

    if (!check(
        rm.unloadMusic("start-music") == -1,
        "Second unload of Music fails gracefully"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Missing files
    // ------------------------------------------------------------

    std::cout << "\n--- Missing File Errors ---"
        << std::endl;

    if (!check(
        rm.loadSprite(
            "Sprites/does_not_exist.txt",
            "missing-sprite") == -1,
        "loadSprite() rejects nonexistent file"))
    {
        failures++;
    }

    if (!check(
        rm.loadSound(
            "Sounds/does_not_exist.wav",
            "missing-sound") == -1,
        "loadSound() rejects nonexistent file"))
    {
        failures++;
    }

    if (!check(
        rm.loadMusic(
            "Sounds/does_not_exist.wav",
            "missing-music") == -1,
        "loadMusic() rejects nonexistent file"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Empty Sprite file
    // ------------------------------------------------------------

    std::cout << "\n--- Empty Sprite File Errors ---"
        << std::endl;

    std::ofstream empty_file(
        "error_empty.txt");

    empty_file.close();

    if (!check(
        rm.loadSprite(
            "error_empty.txt",
            "empty-sprite") == -1,
        "loadSprite() rejects empty file"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid frame count
    // ------------------------------------------------------------

    std::cout << "\n--- Invalid Frame Count Errors ---"
        << std::endl;

    std::ofstream zero_frames(
        "error_zero_frames.txt");

    zero_frames
        << "0\n"
        << "5\n"
        << "3\n"
        << "1\n"
        << "yellow\n";

    zero_frames.close();

    if (!check(
        rm.loadSprite(
            "error_zero_frames.txt",
            "zero-frames") == -1,
        "loadSprite() rejects zero frame count"))
    {
        failures++;
    }

    std::ofstream negative_frames(
        "error_negative_frames.txt");

    negative_frames
        << "-1\n"
        << "5\n"
        << "3\n"
        << "1\n"
        << "yellow\n";

    negative_frames.close();

    if (!check(
        rm.loadSprite(
            "error_negative_frames.txt",
            "negative-frames") == -1,
        "loadSprite() rejects negative frame count"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid width
    // ------------------------------------------------------------

    std::cout << "\n--- Invalid Width Errors ---"
        << std::endl;

    std::ofstream zero_width(
        "error_zero_width.txt");

    zero_width
        << "1\n"
        << "0\n"
        << "3\n"
        << "1\n"
        << "yellow\n"
        << "X\n";

    zero_width.close();

    if (!check(
        rm.loadSprite(
            "error_zero_width.txt",
            "zero-width") == -1,
        "loadSprite() rejects zero width"))
    {
        failures++;
    }

    std::ofstream negative_width(
        "error_negative_width.txt");

    negative_width
        << "1\n"
        << "-5\n"
        << "3\n"
        << "1\n"
        << "yellow\n";

    negative_width.close();

    if (!check(
        rm.loadSprite(
            "error_negative_width.txt",
            "negative-width") == -1,
        "loadSprite() rejects negative width"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid height
    // ------------------------------------------------------------

    std::cout << "\n--- Invalid Height Errors ---"
        << std::endl;

    std::ofstream zero_height(
        "error_zero_height.txt");

    zero_height
        << "1\n"
        << "5\n"
        << "0\n"
        << "1\n"
        << "yellow\n";

    zero_height.close();

    if (!check(
        rm.loadSprite(
            "error_zero_height.txt",
            "zero-height") == -1,
        "loadSprite() rejects zero height"))
    {
        failures++;
    }

    std::ofstream negative_height(
        "error_negative_height.txt");

    negative_height
        << "1\n"
        << "5\n"
        << "-3\n"
        << "1\n"
        << "yellow\n";

    negative_height.close();

    if (!check(
        rm.loadSprite(
            "error_negative_height.txt",
            "negative-height") == -1,
        "loadSprite() rejects negative height"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid slowdown
    // ------------------------------------------------------------

    std::cout << "\n--- Invalid Slowdown Errors ---"
        << std::endl;

    std::ofstream zero_slowdown(
        "error_zero_slowdown.txt");

    zero_slowdown
        << "1\n"
        << "1\n"
        << "1\n"
        << "0\n"
        << "yellow\n"
        << "X\n";

    zero_slowdown.close();

    if (!check(
        rm.loadSprite(
            "error_zero_slowdown.txt",
            "zero-slowdown") == -1,
        "loadSprite() rejects zero slowdown"))
    {
        failures++;
    }

    std::ofstream negative_slowdown(
        "error_negative_slowdown.txt");

    negative_slowdown
        << "1\n"
        << "1\n"
        << "1\n"
        << "-1\n"
        << "yellow\n"
        << "X\n";

    negative_slowdown.close();

    if (!check(
        rm.loadSprite(
            "error_negative_slowdown.txt",
            "negative-slowdown") == -1,
        "loadSprite() rejects negative slowdown"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid color
    // ------------------------------------------------------------

    std::cout << "\n--- Invalid Color Errors ---"
        << std::endl;

    std::ofstream invalid_color(
        "error_invalid_color.txt");

    invalid_color
        << "1\n"
        << "1\n"
        << "1\n"
        << "1\n"
        << "purple\n"
        << "X\n";

    invalid_color.close();

    if (!check(
        rm.loadSprite(
            "error_invalid_color.txt",
            "invalid-color") == -1,
        "loadSprite() rejects unrecognized color"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Missing header fields
    // ------------------------------------------------------------

    std::cout << "\n--- Missing Header Data Errors ---"
        << std::endl;

    std::ofstream missing_width(
        "error_missing_width.txt");

    missing_width << "1\n";
    missing_width.close();

    if (!check(
        rm.loadSprite(
            "error_missing_width.txt",
            "missing-width") == -1,
        "loadSprite() rejects missing width"))
    {
        failures++;
    }

    std::ofstream missing_height(
        "error_missing_height.txt");

    missing_height
        << "1\n"
        << "5\n";

    missing_height.close();

    if (!check(
        rm.loadSprite(
            "error_missing_height.txt",
            "missing-height") == -1,
        "loadSprite() rejects missing height"))
    {
        failures++;
    }

    std::ofstream missing_slowdown(
        "error_missing_slowdown.txt");

    missing_slowdown
        << "1\n"
        << "5\n"
        << "3\n";

    missing_slowdown.close();

    if (!check(
        rm.loadSprite(
            "error_missing_slowdown.txt",
            "missing-slowdown") == -1,
        "loadSprite() rejects missing slowdown"))
    {
        failures++;
    }

    std::ofstream missing_color(
        "error_missing_color.txt");

    missing_color
        << "1\n"
        << "5\n"
        << "3\n"
        << "1\n";

    missing_color.close();

    if (!check(
        rm.loadSprite(
            "error_missing_color.txt",
            "missing-color") == -1,
        "loadSprite() rejects missing color"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Incomplete frame data
    // ------------------------------------------------------------

    std::cout << "\n--- Incomplete Frame Data Errors ---"
        << std::endl;

    std::ofstream missing_frame(
        "error_missing_frame.txt");

    missing_frame
        << "1\n"
        << "3\n"
        << "2\n"
        << "1\n"
        << "yellow\n"
        << "ABC\n";

    missing_frame.close();

    if (!check(
        rm.loadSprite(
            "error_missing_frame.txt",
            "missing-frame") == -1,
        "loadSprite() rejects incomplete frame data"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Row too short
    // ------------------------------------------------------------

    std::ofstream short_row(
        "error_short_row.txt");

    short_row
        << "1\n"
        << "5\n"
        << "2\n"
        << "1\n"
        << "yellow\n"
        << "ABCD\n"
        << "ABCDE\n";

    short_row.close();

    if (!check(
        rm.loadSprite(
            "error_short_row.txt",
            "short-row") == -1,
        "loadSprite() rejects frame row shorter than width"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Row too long
    // ------------------------------------------------------------

    std::ofstream long_row(
        "error_long_row.txt");

    long_row
        << "1\n"
        << "5\n"
        << "2\n"
        << "1\n"
        << "yellow\n"
        << "ABCDEF\n"
        << "ABCDE\n";

    long_row.close();

    if (!check(
        rm.loadSprite(
            "error_long_row.txt",
            "long-row") == -1,
        "loadSprite() rejects frame row longer than width"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Extra frame data
    // ------------------------------------------------------------

    std::ofstream extra_frame(
        "error_extra_frame.txt");

    extra_frame
        << "1\n"
        << "2\n"
        << "2\n"
        << "1\n"
        << "yellow\n"
        << "AB\n"
        << "CD\n"
        << "EXTRA\n";

    extra_frame.close();

    if (!check(
        rm.loadSprite(
            "error_extra_frame.txt",
            "extra-frame") == -1,
        "loadSprite() rejects extra frame data"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Object setSprite() unknown label
    // ------------------------------------------------------------

    Object error_object(Vector(0, 0));

    if (!check(
        error_object.setSprite("does-not-exist") == -1,
        "Object::setSprite() rejects unknown Sprite"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Animation without Sprite
    // ------------------------------------------------------------

    Animation empty_animation;

    if (!check(
        empty_animation.getSprite() == nullptr,
        "New Animation has no Sprite"))
    {
        failures++;
    }

    if (!check(
        empty_animation.draw(Vector(0, 0)) == -1,
        "Animation::draw() rejects missing Sprite"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Empty Frame draw
    // ------------------------------------------------------------

    Frame empty_frame;

    if (!check(
        empty_frame.draw(
            Vector(0, 0),
            WHITE) == -1,
        "Frame::draw() rejects empty frame"))
    {
        failures++;
    }

    // ------------------------------------------------------------
    // Invalid Sprite draw indexes
    // ------------------------------------------------------------

    if (!check(
        capacity_sprite.draw(
            -1,
            Vector(0, 0)) == -1,
        "Sprite::draw() rejects negative frame index"))
    {
        failures++;
    }

    if (!check(
        capacity_sprite.draw(
            capacity_sprite.getFrameCount(),
            Vector(0, 0)) == -1,
        "Sprite::draw() rejects frame index past end"))
    {
        failures++;
    }

    // ============================================================
    // CLEANUP
    // ============================================================

    std::cout << "\n========================================"
        << std::endl;
    std::cout << "CLEANUP"
        << std::endl;
    std::cout << "========================================"
        << std::endl;

    // Remove objects from WorldManager.
    wm.removeObject(&object1);
    wm.removeObject(&object2);

    // Remove edge-case resources.
    rm.unloadSprite("edge-sprite");
    rm.unloadSprite("slowdown-two");

    // Remove base resources.
    rm.unloadSprite("test-sprite");
    rm.unloadSound("fire");
    rm.unloadMusic("start-music");

    // Shut down managers.
    rm.shutDown();
    wm.shutDown();

    // Remove temporary test files.
    std::remove("edge_sprite.txt");
    std::remove("slowdown_two.txt");

    std::remove("error_empty.txt");
    std::remove("error_zero_frames.txt");
    std::remove("error_negative_frames.txt");
    std::remove("error_zero_width.txt");
    std::remove("error_negative_width.txt");
    std::remove("error_zero_height.txt");
    std::remove("error_negative_height.txt");
    std::remove("error_zero_slowdown.txt");
    std::remove("error_negative_slowdown.txt");
    std::remove("error_invalid_color.txt");
    std::remove("error_missing_width.txt");
    std::remove("error_missing_height.txt");
    std::remove("error_missing_slowdown.txt");
    std::remove("error_missing_color.txt");
    std::remove("error_missing_frame.txt");
    std::remove("error_short_row.txt");
    std::remove("error_long_row.txt");
    std::remove("error_extra_frame.txt");

    // ============================================================
    // FINAL RESULT
    // ============================================================

    std::cout << "\n========================================"
        << std::endl;

    if (failures == 0)
    {
        std::cout
            << "ALL 2C TESTS PASSED"
            << std::endl;
    }
    else
    {
        std::cout
            << failures
            << " TEST(S) FAILED"
            << std::endl;
    }

    std::cout << "========================================"
        << std::endl;

    std::cout
        << "ABOUT TO RETURN FROM MAIN"
        << std::endl;

    return failures;
}