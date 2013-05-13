#define SAFE_DELETE(X) if (X) { delete X; X = 0; }
