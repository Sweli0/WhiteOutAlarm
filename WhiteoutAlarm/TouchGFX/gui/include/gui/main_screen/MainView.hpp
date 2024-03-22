#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updateTimeOnAnalogClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void updateTimeFromRTC();
    void startUpdateTimer();
    void startClockUpdateLoop();
    void configureRTCFromPC();
protected:
};

#endif // MAINVIEW_HPP
