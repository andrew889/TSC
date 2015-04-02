#include "../core/global_basic.hpp"
#include "../core/property_helper.hpp"
#include "../scripting/scriptable_object.hpp"
#include "../objects/actor.hpp"
#include "level.hpp"

using namespace TSC;
namespace fs = boost::filesystem;

/**
 * Load a level from a file rather than creating a new one. The
 * level is not active; you have to add it to the cLevelScene
 * manually. Consider using the convenience overload
 * cLevelScene::Add_Level() that accepts a string level name, which
 * does all of this for you.
 *
 * \param levelfile
 * File to load the level from. This will not be touched, the file
 * will be opened exactly as specified; use cPackage_Manager if you
 * want to search for a level’s file path.
 *
 * \returns The loaded level.
 */
cLevel* cLevel::Load_From_File(fs::path levelfile)
{
    // TODO
    return NULL;
}

/**
 * Create a new and empty level. Does NOT load levels from level files,
 * use the Load_From_File() static member function for that. Use
 * cPackage_Manager() to find out the correct saving path.
 *
 * \param levelfile
 * File to save the level to. This will be overwritten if it exists.
 *
 * \returns The new cLevel instance.
 */
cLevel::cLevel(fs::path levelfile)
{
    Init();
}

/**
 * This is a private constructor that is used under the hood by
 * Load_From_File() to create a level that is not yet associated
 * with a file (the public constructor overwrites files).
 */
cLevel::cLevel()
{
    Init();
}

cLevel::~cLevel()
{
    std::vector<sf::Sprite*>::iterator bgiter;
    for(bgiter=m_backgrounds.begin(); bgiter != m_backgrounds.end(); bgiter++)
        delete *bgiter;

    std::vector<cActor*>::iterator actiter;
    for(actiter=m_actors.begin(); actiter != m_actors.end(); actiter++)
        delete *actiter;
}

/**
 * Common basic initialisation for all constructors.
 */
void cLevel::Init()
{
    m_engine_version = 47; // TODO: Should be in the configuration header; currently in global_game.hpp
    m_player_startpos.x = 100;
    m_player_startpos.y = 100;

    m_camera_limits.left = 0;
    m_camera_limits.top = 0;
    m_camera_limits.width = 4000;
    m_camera_limits.height = 1000;
}

void cLevel::Update()
{
    std::vector<cActor*>::iterator iter;
    for(iter=m_actors.begin(); iter != m_actors.end(); iter++)
        (*iter)->Update();
}

void cLevel::Draw(sf::RenderWindow& stage) const
{
    // 1. Draw backgrounds
    std::vector<sf::Sprite*>::const_iterator bgiter;
    for(bgiter=m_backgrounds.begin(); bgiter != m_backgrounds.end(); bgiter++)
        stage.draw(**bgiter);

    // 2. Draw the actors in the level
    std::vector<cActor*>::const_iterator actiter;
    for(actiter=m_actors.begin(); actiter != m_actors.end(); actiter++)
        (*actiter)->Draw(stage);
}
