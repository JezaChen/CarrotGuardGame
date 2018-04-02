#pragma once
#ifndef COMMON_SOURCE_H
#define COMMON_SOURCE_H
#include <string>
using std::string;


const static std::string PHOTOPOSTFIX = ".png";
const static std::string PLISTPOSTFIX = ".plist";

const static std::vector<std::string> ALLSOURCE =
{
    "Themes/scene/mainscene1-hd",
    "Themes/scene/themescene2-hd",
    "Themes/scene/themescene1-hd",
    "Themes/scene/themescene3-hd",
    "Themes/scene/setting01-hd",
    "Themes/scene/setting02-hd",
    "Themes/Items/Items02-hd",
    "Themes/Items/touming-hd",
    "Themes/scene/gamemenu-hd",
    "Themes/scene/weibo-hd",
    "Themes/scene/stages_bg-hd",
    "Themes/Items/Items00-hd",
    "Themes/scene/gameover0-hd",
    "Themes/scene/gameover-hd",
    "Themes/Items/Items01-hd",
    "Themes/scene/help_3-hd",
    "Themes/scene/help_2-hd",
    "Themes/scene/help_1-hd"
}; //所有的资源

/**
*  welcome Scene source
*/
const static std::string WELCOMEBG = "mainbg.png"; //欢迎界面背景
const static std::string WELCOMETITLE = "mainbg_CN.png"; //欢迎界面Title


/**
*  loading source
*/
const static std::string LOADINGSOURCE = "loading/loading.jpeg"; 

const static std::string BG = "theme_bg.png";
const static std::string PAGESOURCE[] =
{
    "theme_pack01.png",
    "theme_pack02.png",
    "theme_pack03.png"
    //    "theme_pack05.png"
};

const static std::string MAPNAME = "ss_map";
const static std::string TOWERNAME = "ss_towers_";
const static unsigned int THEME_LEVELCOUNT_ARRAY[] = { 12, 12, 12, 15 };


const static std::string THEMESSOURCE[] =
{
    "Themes/scene/stages_theme1-hd",
    "Themes/scene/stages_theme2-hd",
    "Themes/scene/stages_theme3-hd",
    "Themes/scene/stages_theme4-hd"
};

#define GAMESCENEBG1 "Themes/Theme%d/BG0/BG1-hd"
#define GAMESCENEBG2 "Themes/Theme%d/BG0/BG2-hd"
#define GAMESCENEMAP "Themes/Theme%d/BG%d/"
#define GAMESCENEBARRIER "Themes/Theme%d/Items/Object01-hd"
#define GAMESCENEMONSTER1 "Themes/Theme%d/Items/Monsters01-hd"
#define GAMESCENEMONSTER2 "Themes/Theme%d/Items/Monsters02-hd"

/**
*  Entity csv files
*/
const static std::string BULLETCSVFILE = "csv/Bullet.csv";
const static std::string BARRIERCSVFILE = "csv/Barrier.csv";
const static std::string TOWERCSVFILE = "csv/Tower.csv";
const static std::string MONSTERCSVFILE = "csv/Monster.csv";
/**
*  level csv config
*/
const static std::string LEVELCSVFILE = "csv/Level.csv";

/**
*  background music and effect sound
*/
const static std::string BACKGROUNDSOUND = "Music/Main/BGMusic.mp3";
const static std::string PRESSEDSOUND = "Music/Main/Select.mp3";
#define THEMEBACKGROUNDMUSIC "Music/Items/BGMusic0%d.mp3"
const static std::string BUILDTOWERSOUND = "Music/Items/TowerBulid.mp3";
const static std::string SELLTOWERSOUND = "Music/Items/TowerSell.mp3";
const static std::string SELECTTOWERSOUND = "Music/Items/TowerSelect.mp3";
const static std::string SELECTVICTIMENTITYBASESOUND = "Music/Main/Unlock.mp3";
const static std::string GAMELOSESOUND = "Music/Items/Lose.mp3";
const static std::string GAMEWINSOUND = "Music/Items/Perfect.mp3";
const static std::string SELECTFAULTSOUND = "Music/Items/SelectFault.mp3";
const static std::string GOSOUND = "Music/Items/GO.mp3";
const static std::string COUNTDOWNSOUND = "Music/Items/CountDown.mp3";
const static std::string UPGRADETOWERSOUND = "Music/Items/TowerUpdata.mp3";
const static std::string CARROTCRASHSOUND = "Music/Items/Crash.mp3";
const static std::string FINALWAVESOUND = "Music/Items/Finalwave.mp3";
#define CARROT "Music/Items/carrot%d.mp3"
const static std::string BUILDMONSTERSOUND = "Music/Items/MC.mp3";
const static std::string MONSTERMUSIC = "Music/Monsters/";


/**
*  theme config info
*/
const static std::string THEME = "Theme";
const static std::string THEMEATTRIBUTE = "ThemeIndex";
/**
*  level config info
*/
const static std::string LEVEL = "Level";
const static std::string LEVELATTRIBUTE = "LevelIndex";
/**
*  monster batch info
*/
const static std::string MONSTERBATCH = "MonsterBatch";
/**
*  towers info
*/
const static std::string TOWER = "TowerType";

/**
*  NumSprite
*/
const static std::string MONEYNUMIMAGE = "Themes/Items/numwhite-hd.png";
const static std::string MONSTERBATCHIMAGE = "Themes/Items/numyellow-hd.png";
const static std::string LITTLENUMIMAGE = "Themes/scene/win_stagenum-hd.png";

/**
*  game End
*/
const static std::vector<std::tuple<std::string, std::string, std::string>> GAMEENDSOURCE =
{
    std::make_tuple(std::string("win_bg.png"), std::string("continue_normal_CN.png"), std::string("continue_pressed_CN.png")),
    std::make_tuple(std::string("lose_bg.png"), std::string("retry_normal_CN.png"), std::string("retry_pressed_CN.png"))
};

const static std::string GAMEENDTITLE = "lose_bg_CN.png";

const static std::vector<std::string> CHOOSESOURCE =
{
    "select_normal_CN.png",
    "select_pressed_CN.png"
};

/**
*  tile size
*/

const static int TILESIZE = 80;

/**
*  carrot hp
*/
const static int GOLDCARROTHP = 10;
const static std::string GOLDCARROT = "gainhonor_3.png";
const static int SILVERCARROTHP1 = 5;
const static int SILVERCARROTHP2 = 9;
const static std::string SILVERCARROT = "gainhonor_2.png";
const static std::string NORMALCARROT = "gainhonor_1.png";
const static std::string BARRIERCLEAN = "gainhonor_4.png";

/**
*  Application config
*/
const static std::string BUILDLEVELDATAKEY = "buildLevelData";
const static std::string DATAFILE = "data.plist";
const static std::string CONFIGFILE = "config.xml";
const static std::string CONFIGBACKGROUND = "backGroundSound";
const static std::string CONFIGEFFECTSOUND = "effectSound";
#define LEVELKEY "%d_%02d"

/**
*  levelconfig type
*ThemeIndex,Level,Money,MonsterBatch,Bollet,Shit,Fan,Star,Ball,FBollet,BStar,Sun1,Rocket,Pin,Snow,Anchor,Bow,BlueBall,PPlane1,Dun,MushRoom,FishBone
*/
const static std::string LEVELCONFIGFILENAME = "level/LevelConfig.xml";
const static std::string LEVELCONFIGROOT = "LevelConfigRoot";
const static std::string TOWERTYPE = "TowerType";
const static std::vector<std::string> LEVELCONFIGTYPE =
{
    "ThemeIndex",
    "Level",
    "Money",
    "MonsterBatch",
    "Bottle",
    "Shit",
    "Fan",
    "Star",
    "Ball",
    "FBottle",
    "BStar",
    "Sun1",
    "Rocket",
    "Pin",
    "Snow",
    "Anchor",
    "Bow",
    "BlueBall",
    "PPlane1",
    "Dun",
    "MushRoom",
    "FishBone"
};

const static std::vector<std::string> TOWERS =
{
    "Themes/Towers/TBottle-hd",
    "Themes/Towers/TFan-hd",
    "Themes/Towers/TShit-hd",
    "Themes/Towers/TStar-hd",
    "Themes/Towers/TBall-hd",
    "Themes/Towers/TFireBottle-hd",
    "Themes/Towers/TBlueStar-hd",
    "Themes/Towers/TSun-hd",
    "Themes/Towers/TPin-hd",
    "Themes/Towers/TSnow-hd",
    "Themes/Towers/TAnchor-hd",
    "Themes/Towers/TPlane-hd",
    "Themes/Towers/TRocket-hd",
    "Themes/Towers/TAnchor-hd"
};
/**
*  NOTIFY message
*/

#define LEVELDATACHANGE "levelDataChange"


#endif // !COMMON_SOURCE_H
