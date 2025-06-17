enum Color {
    RED,
    GREEN,
    BLUE
};

extern const char* __nameof_Color[];

// Force the symbol to be emitted — globally visible definition
__attribute__((used)) const void* _force_emit_color = (const void*)&__nameof_Color;

int main() {
    return 0;
}
