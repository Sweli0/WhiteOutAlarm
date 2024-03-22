#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Application.hpp>
#include "stm32f7xx_hal.h" // Assurez-vous que cette bibliothèque contient les déclarations nécessaires pour accéder à l'horloge en temps réel (RTC)
#include <chrono>   // Pour les opérations temporelles
#include <ctime>    // Pour la conversion du temps en format lisible
#include <iostream> // Pour l'affichage en console
#include <thread>   // Pour la gestion des délais
#include "FreeRTOS.h"
#include "task.h"

extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim1; // Déclarer la structure gérant le timer matériel

MainView::MainView()
{
	 HAL_TIM_Base_Start_IT(&htim1); // Fonction pas terminé : Démarrez le timer en mode interruption}
	 // Configurez la RTC avec l'heure actuelle du PC
	 configureRTCFromPC();
	 // Mettez à jour l'heure sur votre écran
	 updateTimeFromRTC();
}


void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::updateTimeOnAnalogClock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    // Mettre à jour l'heure dans l'AnalogClock
    Hour.setTime24Hour(hours, minutes, seconds);
}

void MainView::updateTimeFromRTC() {
    // Obtenez l'heure actuelle depuis l'horloge en temps réel (RTC)
    RTC_TimeTypeDef time;
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BCD);

    // Mettez à jour l'heure sur votre écran
    updateTimeOnAnalogClock(time.Hours, time.Minutes, time.Seconds);
}

void MainView::configureRTCFromPC() {
    // Obtenez l'heure actuelle du PC
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);

    // Configurez la RTC avec l'heure actuelle du PC
    RTC_TimeTypeDef time;
    time.Hours = localTime->tm_hour;
    time.Minutes = localTime->tm_min;
    time.Seconds = localTime->tm_sec;
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}

