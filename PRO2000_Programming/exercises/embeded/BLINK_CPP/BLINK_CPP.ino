#include <stdint.h>
#include <util/delay.h> // Standard AVR delay utility

// 1. Strongly typed enum for safety
enum class PinState : uint8_t {
    Low  = 0,
    High = 1
};

// 2. Hardware mapping for ATmega328P Port B
struct PortB_Registers {
    volatile uint8_t PIN;  // Input Pins Address (0x23)
    volatile uint8_t DDR;  // Data Direction Register (0x24)
    volatile uint8_t PORT; // Data Register (0x25)
};

// 3. Zero-Overhead C++ Driver Class
class UnoLed {
private:
    // Base address for Port B registers on ATmega328P
    static constexpr uintptr_t PORTB_BASE = 0x23;
    
    // Hardcoded bitmask for Pin 13 (Bit 5 of Port B)
    static constexpr uint8_t LED_PIN_MASK = (1 << 5);

    // Cast the raw memory address to our register structure
    inline PortB_Registers* regs() const {
        return reinterpret_cast<PortB_Registers*>(PORTB_BASE);
    }

public:
    // Standard constructor
    constexpr UnoLed() = default;

    // Configure Port B Pin 5 as an Output
    void init() {
        regs()->DDR |= LED_PIN_MASK;
    }

    // Set LED explicitly On or Off
    void write(PinState state) {
        if (state == PinState::High) {
            regs()->PORT |= LED_PIN_MASK;  // Set bit high
        } else {
            regs()->PORT &= ~LED_PIN_MASK; // Clear bit low
        }
    }

    // Hardware-accelerated toggle 
    // (Writing a '1' to the PIN register toggles an AVR output pin instantly)
    void toggle() {
        regs()->PIN = LED_PIN_MASK;
    }
};

// 4. Main Application Entry Point
int main() {
    UnoLed led;
    led.init(); // Setup Pin 13 as output

    while (true) {
        // Method A: Explicit On/Off using Enums
        led.write(PinState::High);
        _delay_ms(500); // 500 millisecond delay
        
        led.write(PinState::Low);
        _delay_ms(500);

        // Method B: Ultra-fast toggle alternative
        // led.toggle();
        // _delay_ms(500);
    }

    return 0;
}
