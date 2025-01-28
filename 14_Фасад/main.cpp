#include <iostream>
#include <memory>
#include <vector>

// =============================================
// Сложные подсистемы умного дома
// =============================================

// Подсистема освещения
class LightingSystem {
public:
    void SetMainLight(bool state) {
        std::cout << "Основной свет: " << (state ? "ВКЛ" : "ВЫКЛ") << std::endl;
    }

    void SetAmbientLight(int brightness) {
        std::cout << "Фоновое освещение: " << brightness << "%\n";
    }
};

// Подсистема аудио
class AudioSystem {
public:
    void PowerOn() { 
        std::cout << "Аудиосистема: питание ВКЛ\n";
    }
    
    void PlayPlaylist(const std::string& name) {
        std::cout << "Воспроизведение плейлиста: " << name << std::endl;
    }
    
    void SetVolume(int level) {
        std::cout << "Громкость: " << level << "%\n";
    }
};

// Подсистема климат-контроля
class ClimateControl {
public:
    void SetTemperature(float temp) {
        std::cout << "Установлена температура: " << temp << "°C\n";
    }
    
    void SetHumidity(int percent) {
        std::cout << "Влажность: " << percent << "%\n";
    }
};

// Подсистема безопасности
class SecuritySystem {
public:
    void ArmAlarm() {
        std::cout << "Охранная сигнализация: АКТИВИРОВАНА\n";
    }
    
    void DisarmAlarm() {
        std::cout << "Охранная сигнализация: ДЕАКТИВИРОВАНА\n";
    }
};

// =============================================
// Фасад для управления умным домом
// =============================================
class SmartHomeFacade {
    LightingSystem      lighting;
    AudioSystem         audio;
    ClimateControl      climate;
    SecuritySystem      security;
    
public:
    // Режим "Никого нет дома"
    void LeaveHomeMode() {
        std::cout << "\n=== Активация режима 'Уход из дома' ===\n";
        lighting.SetMainLight(false);
        lighting.SetAmbientLight(0);
        audio.PowerOn();
        audio.PlayPlaylist("Тишина");
        audio.SetVolume(0);
        climate.SetTemperature(18.5f);
        security.ArmAlarm();
        std::cout << "======================================\n";
    }

    // Режим "Добро пожаловать домой"
    void WelcomeHomeMode() {
        std::cout << "\n=== Активация режима 'Приветствие' ===\n";
        security.DisarmAlarm();
        lighting.SetMainLight(true);
        lighting.SetAmbientLight(50);
        climate.SetTemperature(22.5f);
        climate.SetHumidity(45);
        audio.PowerOn();
        audio.PlayPlaylist("Расслабляющая музыка");
        audio.SetVolume(25);
        std::cout << "======================================\n";
    }

    // Режим "Кинотеатр"
    void CinemaMode() {
        std::cout << "\n=== Активация режима 'Кинотеатр' ===\n";
        lighting.SetMainLight(false);
        lighting.SetAmbientLight(10);
        climate.SetTemperature(21.0f);
        audio.PowerOn();
        audio.PlayPlaylist("Фильм: Звуковая дорожка");
        audio.SetVolume(60);
        std::cout << "====================================\n";
    }
};

// =============================================
// Клиентский код
// =============================================
int main() {
    SmartHomeFacade smartHome;
    
    // Использование фасада
    smartHome.WelcomeHomeMode();
    smartHome.CinemaMode();
    smartHome.LeaveHomeMode();
    
    // Пример прямого доступа к подсистеме (при необходимости)
    ClimateControl climate;
    climate.SetTemperature(23.5f);  // Ручная настройка
    
    return 0;
}