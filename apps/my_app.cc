// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <mylibrary/location.h>
#include <mylibrary/direction.h>

#include <iostream>
#include <string>

#include "SoundPlayer.h"

using namespace ci::app;
using namespace ci;

const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";

namespace myapp {

    using cinder::app::KeyEvent;

    static void DrawBorder();

    MyApp::MyApp() : player_("adit", 100) {}

    void MyApp::setup() {
        SetUpMusic();
        SetUpGif();
    }

    void MyApp::update() {}

    void MyApp::draw() {
        //  gl::clear(Color(0.5, 0.5, 0.5));
        //  float gray = sin(getElapsedSeconds()) * 0.5f + 0.5f;
        //  gl::color(Color(gray, gray, gray));
        //  gl::drawSolidCircle(getWindowCenter(), 200);
        //  gl::color(Color(1, 1, 1));
        //
        //  gl::translate(140, 100);
        //  gif_->draw();
        //  gl::translate(-140, -100);

        gl::clear(Color::black());
        DrawBorder();
        DrawScoreBoard();
        engine_.DrawPaddle();
        engine_.DrawBall();
    }

/**
 * Prints text
 * @param text std::string - String to print
 * @param color ci::Color - Color of text
 * @param size ivec2 - Size of text
 * @param loc vec2 - Location to print at
 */
    template<typename C>
    void PrintText(const std::string &text, const C &color,
                   const cinder::ivec2 &size, const cinder::vec2 &loc) {
        cinder::gl::color(color);

        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font(kNormalFont, 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
    }

    void MyApp::keyDown(KeyEvent event) {
        switch (event.getCode()) {
//            case KeyEvent::KEY_UP:
//            case KeyEvent::KEY_w: {
//                engine_.SetDirection(Direction::kLeft);
//                break;
//            }
//            case KeyEvent::KEY_DOWN:
//            case KeyEvent::KEY_s: {
//                engine_.SetDirection(Direction::kRight);
//                break;
//            }
            case KeyEvent::KEY_LEFT:
            case KeyEvent::KEY_a: {
                engine_.MovePaddle(brickbreaker::Direction::kLeft);
                break;
            }
            case KeyEvent::KEY_RIGHT:
            case KeyEvent::KEY_d: {
                engine_.MovePaddle(brickbreaker::Direction::kRight);
                break;
            }
            case KeyEvent::KEY_p: {
//                paused_ = !paused_;
//
//                if (paused_) {
//                    last_pause_time_ = system_clock::now();
//                } else {
//                    last_intact_time_ += system_clock::now() - last_pause_time_;
//                }
                break;
            }
            case KeyEvent::KEY_r: {
//                ResetGame();
                break;
            }
        }
    }

/**
 * Draws game right-edge border
 */
    static void DrawBorder() {
        gl::color(Color::white());
        gl::drawSolidRect(Rectf(800, 0, 802, 600));
    }

/**
 * Prints out the current score and number of lives left
 */
    void MyApp::DrawScoreBoard() {
        const cinder::vec2 loc_score(900, 130);
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();
        std::string to_print = "Score: " + std::to_string(engine_.Score());
        PrintText(to_print, color, size, loc_score);

        const cinder::vec2 loc_lives(900, 600 - 130);
        to_print = "Lives Left: " + std::to_string(engine_.Lives());
        PrintText(to_print, color, size, loc_lives);
    }

/**
 * Starts background music (looped)
 */
    void MyApp::SetUpMusic() {
        sound_track_ = rph::SoundPlayer::create(loadAsset("temp.mp3"));
        sound_track_->setLoop(true);
        sound_track_->setVolume(1.0);
        //  sound_track_->start();
    }

/**
 * Initializes GIF
 */
    void MyApp::SetUpGif() { gif_ = ciAnimatedGif::create(loadAsset("temp.gif")); }

}  // namespace myapp
