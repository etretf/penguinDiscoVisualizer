#pragma once

#include "ofMain.h"
#include "AudioAnalyser.h"
#include "Config.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    AudioAnalyser m_audioAnalyser;
    bool m_paused;
    bool m_toggleUI;

    //object positions
    ofVec2f m_mousePos;
    ofVec2f m_ufoPos;
    ofVec2f m_targetUfoPos;
    ofVec2f m_moonPos;
    ofVec2f m_ufoGroupPos;
    ofVec2f m_penguinPos;

    //city/sky images
    ofImage m_cityImage;
    ofImage m_nightBgImage;
    ofImage m_spaceBgImage;
    ofImage m_moonImage;
    ofImage m_ufoImage;
    ofImage m_ufoLightsImage;
    ofImage m_redUfoImage;
    ofImage m_yellowUfoImage;
    ofImage m_greenUfoImage;
    ofImage m_blueUfoImage;
    ofImage m_pinkUfoImage;
    ofImage m_abductingUfoImage;
    ofImage m_morningImage;

    ofVec3f m_cityPos;    
    ofImage m_redLightsLeftImage;
    ofImage m_yellowLightsImage;
    ofImage m_greenLightsImage;
    ofImage m_blueLightsImage;
    ofImage m_redLightsRightImage;
    ofImage m_pinkLightsImage;
    ofImage m_yellow1Image;
    ofImage m_yellow2Image;
    ofImage m_yellow3Image;
    ofImage m_yellow4Image;

    //boombox images
    ofImage m_ampImage;
    ofImage m_boomboxDoorImage;

    //disco images
    ofImage m_discoFloorImage;
    ofImage m_discoFloor2Image;
    ofImage m_radialImage;
    ofImage m_discoBallImage;

    ofImage m_discoRedImage;
    ofImage m_discoYellowImage;
    ofImage m_discoGreenImage;
    ofImage m_discoBlueImage;
    ofImage m_discoPinkImage;

    //dance arrow images
    ofImage m_arrowsImage;
    ofImage m_leftArrowImage;
    ofImage m_upArrowImage;
    ofImage m_rightArrowImage;
    ofImage m_downArrowImage;

    //penguin images
    ofImage m_penguinIdleImage;
    ofImage m_penguinLeftImage;
    ofImage m_penguinRightImage;
    ofImage m_penguinUpImage;
    ofImage m_penguinDownImage;
    ofImage m_penguinLeft2Image;
    ofImage m_penguinRight2Image;
    ofImage m_penguinsLeftImage;
    ofImage m_penguinsRightImage;
    ofImage m_penguinsLeft2Image;
    ofImage m_penguinsRight2Image;
    ofImage m_penguinDoorCityImage;

    bool isDancingLeft;

    enum m_keypress{ IDLE, LEFT, RIGHT, UP, DOWN };
    int m_currKey;
    float m_currentTime;

    float m_skyOpacity;


    float           m_bassdrum_tone1;
    float           m_tone2;
    float           m_tone3;
    float           m_tone4;
    float           m_tone5;
    float           m_snare_tone6;
    float           m_hihat_tone7;
    float           m_tone8;

    float lerp(float start, float end, float percent);
    void getTones();
    void drawDebug();
    void drawScene1();
    void drawScene2();
    void drawScene3();
    void drawScene4();
    void drawScene5();
    void drawScene6();
};
