//Emma Souannhaphanh
//IMD3005
//Assignment 4: Audio Interaction

#include "ofApp.h"

void ofApp::setup() 
{
	ofSetVerticalSync(true);
    ofSetWindowShape( 1280, 900 );

    //load images
    m_moonImage.load("Moon.png");
    m_cityImage.load("lightsoffBox.png");
    m_morningImage.load("morning.png");
    m_nightBgImage.load("Nightbg.png");
    m_spaceBgImage.load("space.png");
    //ufo images
    m_ufoImage.load("ufo.png");
    m_ufoLightsImage.load("ufoLights.png");
    m_redUfoImage.load("redUfo.png");
    m_yellowUfoImage.load("yellowUfo.png");
    m_greenUfoImage.load("greenUfo.png");
    m_blueUfoImage.load("blueUfo.png");
    m_pinkUfoImage.load("pinkUfo.png");
    m_abductingUfoImage.load("abductingUFO.png");


    //city lights
    m_redLightsLeftImage.load("red lights left.png");
    m_yellowLightsImage.load("yellow lights.png");
    m_greenLightsImage.load("green lights.png");
    m_blueLightsImage.load("blue lights.png");
    m_redLightsRightImage.load("red lights right.png");
    m_pinkLightsImage.load("pink lights.png");

    m_yellow1Image.load("tone1 yellow.png");
    m_yellow2Image.load("tone2 yellow.png");
    m_yellow3Image.load("tone3 yellow.png");
    m_yellow4Image.load("tone4 yellow.png");

    //disco club  images
    m_boomboxDoorImage.load("boomboxDoor.png");
    m_ampImage.load("amp.png");

    m_discoFloorImage.load("discofloor.png");
    m_discoFloor2Image.load("discoFloor2.png");
    m_radialImage.load("clubbg.png");
    m_discoBallImage.load("discoBall.png");

    m_discoRedImage.load("discoRed.png");
    m_discoYellowImage.load("discoYellow.png");
    m_discoGreenImage.load("discoGreen.png");
    m_discoBlueImage.load("discoBlue.png");
    m_discoPinkImage.load("discoPink.png");

    //arrow images
    m_arrowsImage.load("arrows.png");
    m_leftArrowImage.load("leftArrow.png");
    m_upArrowImage.load("upArrow.png");
    m_downArrowImage.load("downArrow.png");
    m_rightArrowImage.load("rightArrow.png");

    //penguin images
    m_penguinIdleImage.load("penguin idle.png");
    m_penguinLeftImage.load("penguin left.png");
    m_penguinRightImage.load("penguin right.png");
    m_penguinUpImage.load("penguin up.png");
    m_penguinDownImage.load("penguin down.png");
    m_penguinLeft2Image.load("penguin left 2.png");
    m_penguinRight2Image.load("penguin right 2.png");

    //penguin group images
    m_penguinsLeftImage.load("penguinsLeft.png");
    m_penguinsRightImage.load("penguinsRight.png");
    m_penguinsLeft2Image.load("penguinsLeft2.png");
    m_penguinsRight2Image.load("penguinsRight2.png");
    m_penguinDoorCityImage.load("abductPenguin.png");

    //init vars
    m_paused = false;
    m_toggleUI = false;

    //city image position
    m_cityPos = ofVec2f(0, 0);

    //keypress init var
    m_currKey = IDLE; //0 or no key pressed


    //UFO initial vector
    m_ufoPos = ofVec2f::zero();

    //UFO group initial vector
    m_ufoGroupPos = ofVec2f::zero();

    //moon position
    m_moonPos = ofVec2f(ofGetWidth() / 2.0f, 900.0f);

    //ending sunrise image opacity
    m_skyOpacity = 0.0f;

    m_audioAnalyser.init("kkHouse.mp3", 8);
	m_audioAnalyser.setLoop(true);
	m_audioAnalyser.play();
}

void ofApp::update() 
{
    //update the current time
    m_currentTime = m_audioAnalyser.getPositionMS() / 1000.0f;

    //do not update analyser if the music is pause
    if (m_paused == false)
    {
        m_audioAnalyser.update();
    }

    //update the UFO position based on the mouse position
    m_mousePos = ofVec2f((float)ofGetMouseX(), (float)ofGetMouseY());
    ofVec2f vecToMouse = m_mousePos - m_ufoPos;

    m_ufoPos.x = lerp(m_ufoPos.x, m_targetUfoPos.x - m_ufoImage.getWidth()/2.0f, 0.03f);
    m_ufoPos.y = lerp(m_ufoPos.y, m_targetUfoPos.y, 0.03f);


    //scene 1: moving the moon up into the sky
    if (m_moonPos.y > (ofGetHeight() - 900.0f) && m_currentTime < Config::scene1End)
        m_moonPos.y = -(m_audioAnalyser.getPositionMS() / 50.0f) + 900.0f;

    //setting the moon position once it reaches a certain height
    if (m_moonPos.y < (ofGetHeight() / 2.0f - 100.0f))
        m_moonPos.y = ofGetHeight() / 2.0f - 100.0f;

    //setting the city position to 0 if not between 8-16 seconds (scene 1)
    if (m_currentTime < 8.0f || (m_currentTime > Config::scene1End && m_currentTime < 63.0f))
        m_cityPos.x = 0.0f;    
    //scene 1: moving the city position to the left
    if (m_currentTime > 8.0f && m_currentTime < 15.5f)
        m_cityPos.x = -(m_audioAnalyser.getPositionMS() /1000.0f - 8.0f) * 100.0f;
    
    //if before scene 3
    if (m_currentTime < Config::scene2End)
    {
        m_ufoGroupPos.y = 0.0f;
    }
    //if during scene 3: move all UFOs down until y = 260.0f
    else if (m_currentTime > Config::scene2End && m_ufoGroupPos.y < 260.0f)
    {
        m_ufoGroupPos.y = (m_audioAnalyser.getPositionMS() / 1000.0f - 47.0f) * 25.0f;
    }
    else if(m_ufoGroupPos.y > 260.0f)
    {
        m_ufoGroupPos.y = 260.0f;
    }
    //if during second half of scene 3, move city to the left
    if (m_currentTime > 63.0f && m_currentTime < 72.5f)
    {
        m_cityPos.x = -(m_audioAnalyser.getPositionMS() / 1000.0f - 63.0f) * 82.0f;
    }
    //if during last scene, increase the sunrise background opacity
    if (m_currentTime > Config::scene5End)
    {
        m_skyOpacity = (m_audioAnalyser.getPositionMS() / 1000.0f - 110.0f) * 8.0f;
        m_moonPos.y = ofGetHeight() / 2.0f - 200.0f;
    }
    //lower the moon
    if (m_currentTime > Config::scene5End + 4.0f)
    {
        m_moonPos.y = ofGetHeight() / 2.0f - 200.0f + (m_audioAnalyser.getPositionMS() / 1000.0f - 114.0f) * 40.0f;
    }

    getTones(); //calculate tone range frequency levels

    //penguins dancing in club - set direction based on snare hit
    if (m_snare_tone6 > 0.4f)
    {
        if (ofGetElapsedTimef() > 0.8f)
        {
            isDancingLeft = !isDancingLeft;
            ofResetElapsedTimeCounter();
        }       
    }
}


void ofApp::draw() 
{
    //UI view
    if (m_toggleUI == true)
    {
        drawDebug();
    }
    else //draw scene based on song time
    {
        if (m_currentTime < Config::scene1End)
            drawScene1();
        if (m_currentTime >= Config::scene1End && m_currentTime < Config::scene2End)
            drawScene2();
        if (m_currentTime >= Config::scene2End && m_currentTime < Config::scene3End)
            drawScene3();
        if (m_currentTime >= Config::scene3End && m_currentTime < Config::scene4End)
            drawScene4();
        if (m_currentTime >= Config::scene4End && m_currentTime < Config::scene5End)
            drawScene5();
        if (m_currentTime >= Config::scene5End)
            drawScene6();
    }

}

void ofApp::keyPressed(int key) {
    if (key == 32) //spacebar
    {   
        m_toggleUI = !m_toggleUI;
    }
    if (key == 'S' || key == 's') //pause/play
    {
        m_paused = !m_paused;
        if (m_paused == true)
            m_audioAnalyser.setPaused(true);
        else m_audioAnalyser.setPaused(false);
    }
    if (key == 'A' || key == 'a')//go back one second
    {
        m_audioAnalyser.setPositionMS(m_audioAnalyser.getPositionMS() - 1 * 1000);

    }
    if (key == 'D' || key == 'd')//go forward one second
    {
        m_audioAnalyser.setPositionMS(m_audioAnalyser.getPositionMS() + 1 * 1000);
    }
    if (key == OF_KEY_LEFT)//dance left
    {
        m_currKey = LEFT;
    }
    if (key == OF_KEY_UP)//dance up
    {
        m_currKey = UP;
    }
    if (key == OF_KEY_DOWN)//dance down
    {
        m_currKey = DOWN;
    }
    if (key == OF_KEY_RIGHT)//dance right
    {
        m_currKey = RIGHT;
    }
}

//go back to no key pressed on any arrow key release so penguin will be idle
void ofApp::keyReleased(int key)
{
    if (key == OF_KEY_LEFT)
    {
        m_currKey = IDLE;
    }
    if (key == OF_KEY_UP)
    {
        m_currKey = IDLE;

    }
    if (key == OF_KEY_DOWN)
    {
        m_currKey = IDLE;
    }
    if (key == OF_KEY_RIGHT)
    {
        m_currKey = IDLE;
    }
}

void ofApp::mouseDragged(int x, int y, int button)
{
    m_targetUfoPos.set(ofVec2f((float)x, (float)y)); //set target position of UFO
}

void ofApp::mousePressed(int x, int y, int button)
{
    m_targetUfoPos.set(ofVec2f((float)x, (float)y)); //set target position of UFO
}

float ofApp::lerp(float start, float end, float percent)
{
    return (start + percent * (end - start));
}

void ofApp::getTones()
{
    //Get decibel levels for tones
    float bassdrum = m_audioAnalyser.getLinearAverage(0);
    float tone1 = m_audioAnalyser.getLinearAverage(27);
    float tone2 = m_audioAnalyser.getLinearAverage(32);
    float tone3 = (m_audioAnalyser.getLinearAverage(36) + m_audioAnalyser.getLinearAverage(37)) / 2.0f;
    float tone4 = (m_audioAnalyser.getLinearAverage(40) + m_audioAnalyser.getLinearAverage(41)) / 2.0f;
    float snare = m_audioAnalyser.getLinearAverage(57);
    float hihat = m_audioAnalyser.getLinearAverage(64);
    float tone8 = (m_audioAnalyser.getLinearAverage(35) + m_audioAnalyser.getLinearAverage(47)) / 2.0f;

    //Map tone levels to be [0.0f, 1.0f]
    m_bassdrum_tone1 = ofMap(bassdrum, 30.0f, 60.0f, 0.0f, 1.0f, true);
    m_tone2 = ofMap(tone1, 50.0f, 100.0f, 0.0f, 1.0f, true);
    m_tone3 = ofMap(tone2, 40.0f, 50.0f, 0.0f, 1.0f, true);
    m_tone4 = ofMap(tone3, 35.0f, 50.0f, 0.0f, 1.0f, true);
    m_tone5 = ofMap(tone4, 35.0f, 50.0f, 0.0f, 1.0f, true);
    m_snare_tone6 = ofMap(snare, 6.0f, 13.0f, 0.0f, 1.0f, true);
    m_hihat_tone7 = ofMap(hihat, 0.0f, 3.0f, 0.0f, 1.0f, true);
    m_tone8 = ofMap(tone8, 13.0f, 20.0f, 0.0f, 1.0f, true);
}

void ofApp::drawDebug()
{
    ofBackground(ofColor::black);
    ofSetColor(255);

    // Volume Level
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Volume Level", 140, 50);

    ofDrawCircle(100, 100, m_audioAnalyser.getLeftLevel() * 100.0f);
    ofDrawCircle(200, 100, m_audioAnalyser.getRightLevel() * 100.0f);
    ofDrawCircle(300, 100, m_audioAnalyser.getMixLevel() * 100.0f);

    ofDrawBitmapString("Left", 80, 170);
    ofDrawBitmapString("Right", 180, 170);
    ofDrawBitmapString("Mix", 290, 170);


    // Frequency / FFT information
    m_audioAnalyser.drawWaveform(40, 310, 1200, 90);
    m_audioAnalyser.drawSpectrum(40, 470, 1200, 128);

    m_audioAnalyser.drawLinearAverages(40, 650, 1200, 128);

    // Draw circles to indicate activity in the frequency ranges we are interested in
    ofSetColor(ofFloatColor(m_bassdrum_tone1, 0.0f, 0.0f));
    ofDrawCircle(440, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Bass/Kick Drum", 390, 170);

    ofSetColor(ofFloatColor(0.0f, m_tone2, 0.0f));
    ofDrawCircle(570, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Tone 1", 550, 170);

    ofSetColor(ofFloatColor(0.0f, m_tone3, 0.0f));
    ofDrawCircle(670, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Tone 2", 650, 170);

    ofSetColor(ofFloatColor(0.0f, m_tone4, 0.0f));
    ofDrawCircle(770, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Tone 3", 750, 170);

    ofSetColor(ofFloatColor(0.0f, m_tone5, 0.0f));
    ofDrawCircle(870, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Tone 4", 850, 170);

    ofSetColor(ofFloatColor(0.0f, 0.0f, m_snare_tone6));
    ofDrawCircle(970, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Snare", 950, 170);

    ofSetColor(ofFloatColor(1.0f, 1.0f, 1.0f, m_hihat_tone7));
    ofDrawCircle(1070, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Hi-hat", 1045, 170);

    ofSetColor(ofFloatColor(1.0f, 1.0f, 1.0f, m_tone8));
    ofDrawCircle(1170, 100, 30);
    ofSetColor(255);
    ofDrawBitmapString("Ddo", 1155, 170);


    ofSetColor(ofColor::white);

    float songTimeSeconds = m_audioAnalyser.getPositionMS() / 1000.0f;
    ofDrawBitmapString("Song time: " + ofToString(songTimeSeconds), 40, 250);
    ofDrawBitmapString("Go back - A.", 200, 250);
    ofDrawBitmapString("Go forwards - D.", 200, 270);
    ofDrawBitmapString("Pause/Play - S.", 200, 290);
}

//Scene 1: city lights, then move to show boombox disco club
void ofApp::drawScene1()
{
    ofBackground(ofColor::white);
    ofSetColor(255);
    m_nightBgImage.draw(0, 0);

    //draw moon
    ofSetRectMode(OF_RECTMODE_CENTER);
    m_moonImage.draw(m_moonPos.x, m_moonPos.y - m_moonImage.getHeight()/2.0f, m_moonImage.getWidth() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f, m_moonImage.getHeight() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    //draw buildings and lights
    ofPushMatrix();
    {
        ofTranslate(m_cityPos);
        m_cityImage.draw(0, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        m_ampImage.draw(1421.0f + m_ampImage.getWidth() / 2.0f, 646.0f + m_ampImage.getHeight() / 2.0f, m_ampImage.getWidth() + m_audioAnalyser.getMixLevel() * 300.0f, m_ampImage.getHeight() + m_audioAnalyser.getMixLevel() * 300.0f);
        m_ampImage.draw(1755.0f + m_ampImage.getWidth() / 2.0f, 646.0f + m_ampImage.getHeight() / 2.0f, m_ampImage.getWidth() + m_audioAnalyser.getMixLevel() * 300.0f, m_ampImage.getHeight() + m_audioAnalyser.getMixLevel() * 300.0f);
        ofSetRectMode(OF_RECTMODE_CORNER);
        //whistle tone window lights
        ofSetColor(ofFloatColor(1.0f, m_tone2));
        m_yellow1Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone3));
        m_yellow2Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone4));
        m_yellow3Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone5));
        m_yellow4Image.draw(0, 0);

        //drum tones window lights

        ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
        m_redLightsLeftImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_snare_tone6));
        m_greenLightsImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_hihat_tone7));
        m_pinkLightsImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_snare_tone6 + 0.2f));
        m_boomboxDoorImage.draw(0, 0);
    }
    ofPopMatrix();
}


//Scene 2: penguin disco night club
void ofApp::drawScene2()
{
    ofPushMatrix();
    {
        m_radialImage.draw(0, 0);
        ofSetColor(255);
        m_discoFloorImage.draw(0, 0);

        ofSetRectMode(OF_RECTMODE_CENTER);
        m_discoBallImage.draw(ofGetWidth() / 2.0f, 120.0f,
            ofLerp(m_discoBallImage.getWidth() * 0.5f, m_discoBallImage.getWidth() * 0.5f + m_audioAnalyser.getMixLevel() * 1000.0f, 0.3f),
            ofLerp(m_discoBallImage.getHeight() * 0.5f, m_discoBallImage.getHeight() * 0.5f + m_audioAnalyser.getMixLevel() * 1000.0f, 0.3f));
        ofSetRectMode(OF_RECTMODE_CORNER);

        ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
        m_discoRedImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
        m_discoPinkImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_snare_tone6));
        m_discoYellowImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_hihat_tone7));
        m_discoBlueImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone8));
        m_discoGreenImage.draw(0, 0);

        ofSetColor(255); 
        if (isDancingLeft) //draw penguins in background dancing left or right
            m_penguinsLeftImage.draw(0, 0);
        else
            m_penguinsRightImage.draw(0, 0);

        m_arrowsImage.draw(0, 0);

        switch (m_currKey)
        {
        case LEFT:
            m_leftArrowImage.draw(0, 0);
            break;
        case RIGHT:
            m_rightArrowImage.draw(0,0);
            break;
        case UP:
            m_upArrowImage.draw(0, 0);
            break;
        case DOWN:
            m_downArrowImage.draw(0, 0);
            break;
        }

        ofTranslate(ofGetWidth()/2.0f - m_penguinIdleImage.getWidth()/2.0f, 400);
        ofSetColor(255);
        switch (m_currKey)
        {
        case IDLE:
            m_penguinIdleImage.draw(0, 0);
            break;
        case LEFT:
            m_penguinLeftImage.draw(0, 0);
            break;
        case RIGHT:
            m_penguinRightImage.draw(0, 0);
            break;
        case UP:
            m_penguinUpImage.draw(0, 0);
            break;
        case DOWN:
            m_penguinDownImage.draw(0, 0);
            break;
        default:
            m_penguinIdleImage.draw(0, 0);
            break;
        }
    }
    ofPopMatrix();
}

//Scene 3: return to the city and UFOs have appeared to enjoy the music
void ofApp::drawScene3()
{
    ofBackground(ofColor::white);
    ofSetColor(255);
    ofSetColor(255);
    m_nightBgImage.draw(0, 0);

    ofSetRectMode(OF_RECTMODE_CENTER);
    m_moonImage.draw(m_moonPos.x, m_moonPos.y - m_moonImage.getHeight() / 2.0f, m_moonImage.getWidth() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f, m_moonImage.getHeight() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f);
    ofSetRectMode(OF_RECTMODE_CORNER);

    //draw city and lights
    ofPushMatrix();
    {
        ofTranslate(m_cityPos);
        m_cityImage.draw(0, 0);
        m_penguinDoorCityImage.draw(0, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        m_ampImage.draw(1421.0f + m_ampImage.getWidth() / 2.0f, 646.0f + m_ampImage.getHeight() / 2.0f, m_ampImage.getWidth() + m_audioAnalyser.getMixLevel() * 300.0f, m_ampImage.getHeight() + m_audioAnalyser.getMixLevel() * 300.0f);
        m_ampImage.draw(1755.0f + m_ampImage.getWidth() / 2.0f, 646.0f + m_ampImage.getHeight() / 2.0f, m_ampImage.getWidth() + m_audioAnalyser.getMixLevel() * 300.0f, m_ampImage.getHeight() + m_audioAnalyser.getMixLevel() * 300.0f);
        ofSetRectMode(OF_RECTMODE_CORNER);

        //whistle tone window lights
        ofSetColor(ofFloatColor(1.0f, m_tone2));
        m_yellow1Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone3));
        m_yellow2Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone4));
        m_yellow3Image.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_tone5));
        m_yellow4Image.draw(0, 0);

        //drum tones window lights

        ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
        m_redLightsLeftImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_snare_tone6));
        m_greenLightsImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_hihat_tone7));
        m_pinkLightsImage.draw(0, 0);

        ofSetColor(ofFloatColor(1.0f, m_snare_tone6 + 0.2f));
        m_boomboxDoorImage.draw(0, 0);
    }
    ofPopMatrix();


    //draw UFOs with lights
    ofPushMatrix();
    {
        ofTranslate(m_ufoGroupPos);

        ofSetColor(255);
        m_ufoImage.draw(110.0f, sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);
        if (m_bassdrum_tone1 > 0.6f)
            m_redUfoImage.draw(110.0f, sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);

        m_ufoImage.draw(358.0f, -150.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);
        if(m_tone2 > 0.6f || m_tone3 > 0.6f)
            m_yellowUfoImage.draw(358.0f, -150.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);

        m_ufoImage.draw(597.0f, 160.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 798.0f) * 20.0f);
        if (m_snare_tone6 > 0.2f)
            m_greenUfoImage.draw(597.0f, 160.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 798.0f) * 20.0f);

        m_ufoImage.draw(827.0f, -120.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);
        if (m_tone4 > 0.4f || m_tone5 > 0.4f)
            m_yellowUfoImage.draw(827.0f, -120.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);

        m_ufoImage.draw(1068.0f, 100.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);
        if (m_hihat_tone7 > 0.3f)
            m_pinkUfoImage.draw(1068.0f, 100.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);
    }
    ofPopMatrix();

    //draw UFO you control
    ofPushMatrix();
    {
        ofSetColor(255);
        ofTranslate(m_ufoPos);
        m_ufoImage.draw(0, 0);
        if (m_snare_tone6 > 0.2f)
            m_blueUfoImage.draw(0, 0);
    }
    ofPopMatrix();

    ofSetColor(255);
}

//Scene 4: penguin is abducted by UFOs and dances in the air
void ofApp::drawScene4()
{
    ofSetColor(255);
    m_spaceBgImage.draw(0, -m_spaceBgImage.getHeight() + (m_audioAnalyser.getPositionMS() / 1000.0f - 78.0f) * 20.0f);
    m_spaceBgImage.draw(0, (m_audioAnalyser.getPositionMS() / 1000.0f - 78.0f) * 20.0f);

    //draw oscillating UFOs
    ofSetColor(255);
    m_ufoImage.draw(68.0f, 454.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);
    if (m_bassdrum_tone1 > 0.6f)
        m_redUfoImage.draw(68.0f, 454.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);

    m_ufoImage.draw(260.0f, 171.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);
    if (m_tone2 > 0.6f || m_tone3 > 0.6f)
        m_yellowUfoImage.draw(260.0f, 171.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);

    m_ufoImage.draw(297.0f, 673.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 798.0f) * 20.0f);
    if (m_snare_tone6 > 0.2f)
        m_greenUfoImage.draw(297.0f, 673.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 798.0f) * 20.0f);

    m_ufoImage.draw(947.0f, 171.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);
    if (m_tone4 > 0.4f || m_tone5 > 0.4f)
        m_yellowUfoImage.draw(947.0f, 171.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);

    m_ufoImage.draw(1081.0f, 514.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);
    if (m_hihat_tone7 > 0.3f)
        m_pinkUfoImage.draw(1081.0f, 514.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);

    //draw arrows
    m_arrowsImage.draw(0, 0);
    ofPushMatrix();
    {
        ofTranslate(0.0f, sin(m_audioAnalyser.getPositionMS() / 1000.0f - 78.0f) * 10.0f);
        m_abductingUfoImage.draw(ofGetWidth() / 2.0f - m_abductingUfoImage.getWidth() / 2.0f, -200.0f);
        switch (m_currKey)
        {
        case LEFT:
            m_leftArrowImage.draw(0, 0);
            break;
        case RIGHT:
            m_rightArrowImage.draw(0, 0);
            break;
        case UP:
            m_upArrowImage.draw(0, 0);
            break;
        case DOWN:
            m_downArrowImage.draw(0, 0);
            break;
        }
        //draw penguin dancing
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth() / 2.0f - m_penguinIdleImage.getWidth() / 2.0f, 400);
            ofSetColor(255);
            switch (m_currKey)
            {
            case IDLE:
                m_penguinIdleImage.draw(0, 0);
                break;
            case LEFT:
                m_penguinLeft2Image.draw(0, 0);
                break;
            case RIGHT:
                m_penguinRight2Image.draw(0, 0);
                break;
            case UP:
                m_penguinUpImage.draw(0, 0);
                break;
            case DOWN:
                m_penguinDownImage.draw(0, 0);
                break;
            default:
                m_penguinIdleImage.draw(0, 0);
                break;
            }
        }
        ofPopMatrix();
    }
    ofPopMatrix();

}

//Scene 5: penguin disco in space
void ofApp::drawScene5()
{
    m_spaceBgImage.draw(0, -m_spaceBgImage.getHeight() + (m_audioAnalyser.getPositionMS() / 1000.0f - 86.0f) * 20.0f);
    m_spaceBgImage.draw(0, (m_audioAnalyser.getPositionMS() / 1000.0f - 86.0f) * 20.0f);
    ofSetColor(255);

    ofSetRectMode(OF_RECTMODE_CENTER);
    m_moonImage.draw(ofGetWidth() / 2.0f, 200.0f, m_moonImage.getWidth() + m_audioAnalyser.getMixLevel() * 600.0f, m_moonImage.getHeight() + m_audioAnalyser.getMixLevel() * 600.0f);
    ofSetRectMode(OF_RECTMODE_CORNER);

    //draw dance floor
    ofSetColor(255);
    m_discoFloor2Image.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
    m_discoRedImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
    m_discoPinkImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_snare_tone6));
    m_discoYellowImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_hihat_tone7));
    m_discoBlueImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_tone8));
    m_discoGreenImage.draw(0, 0);

    //draw penguins dancing in background
    ofSetColor(255);
    if (isDancingLeft)
        m_penguinsLeft2Image.draw(0, 0);
    else
        m_penguinsRight2Image.draw(0, 0);

    
    //draw arrows
    m_arrowsImage.draw(0, 0);
    switch (m_currKey)
    {
    case LEFT:
        m_leftArrowImage.draw(0, 0);
        break;
    case RIGHT:
        m_rightArrowImage.draw(0, 0);
        break;
    case UP:
        m_upArrowImage.draw(0, 0);
        break;
    case DOWN:
        m_downArrowImage.draw(0, 0);
        break;
    }
    //draw penguin dancing - now with a new dance move
    ofPushMatrix();
    {
        ofTranslate(ofGetWidth() / 2.0f - m_penguinIdleImage.getWidth() / 2.0f, 400);
        ofSetColor(255);
        switch (m_currKey)
        {
        case IDLE:
            m_penguinIdleImage.draw(0, 0);
            break;
        case LEFT:
            m_penguinLeft2Image.draw(0, 0);
            break;
        case RIGHT:
            m_penguinRight2Image.draw(0, 0);
            break;
        case UP:
            m_penguinUpImage.draw(0, 0);
            break;
        case DOWN:
            m_penguinDownImage.draw(0, 0);
            break;
        default:
            m_penguinIdleImage.draw(0, 0);
            break;
        }
    }
    ofPopMatrix();

    //draw UFOs
    m_ufoImage.draw(63.0f, 70.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);
    if (m_bassdrum_tone1 > 0.6f)
        m_redUfoImage.draw(63.0f, 70.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f) * 20.0f);

    m_ufoImage.draw(260.0f, 62.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);
    if (m_hihat_tone7 > 0.3f)
        m_blueUfoImage.draw(260.0f, 62.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 123.0f) * 20.0f);


    m_ufoImage.draw(947.0f, 51.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);
    if (m_snare_tone6 > 0.2f)
        m_yellowUfoImage.draw(947.0f, 51.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 422.0f) * 20.0f);

    m_ufoImage.draw(1132.0f, 102.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);
    if (m_bassdrum_tone1 > 0.6f)
        m_pinkUfoImage.draw(1132.0f, 102.0f + sin(m_audioAnalyser.getPositionMS() / 500.0f + 300.0f) * 20.0f);
}

//Scene 6: return to the city. The night is over, and the sun is rising.
void ofApp::drawScene6()
{
    ofBackground(ofColor::white);
    ofSetColor(255);
    m_nightBgImage.draw(0, 0);

    ofSetRectMode(OF_RECTMODE_CENTER);
    m_moonImage.draw(m_moonPos.x, m_moonPos.y, m_moonImage.getWidth() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f, m_moonImage.getHeight() * 0.5f + m_audioAnalyser.getMixLevel() * 600.0f);
    ofSetRectMode(OF_RECTMODE_CORNER);

    m_cityImage.draw(0, 0);
    //whistle tone window lights
    ofSetColor(ofFloatColor(1.0f, m_tone2));
    m_yellow1Image.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_tone3));
    m_yellow2Image.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_tone4));
    m_yellow3Image.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_tone5));
    m_yellow4Image.draw(0, 0);

    //drum tones window lights

    ofSetColor(ofFloatColor(1.0f, m_bassdrum_tone1));
    m_redLightsLeftImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_snare_tone6));
    m_greenLightsImage.draw(0, 0);

    ofSetColor(ofFloatColor(1.0f, m_hihat_tone7));
    m_pinkLightsImage.draw(0, 0);

    ofSetColor(255.0f, 255.0f, 255.0f, m_skyOpacity);
    m_morningImage.draw(0, 0);
    ofSetColor(255);
}

