# LifeGame Modern C++ (OpenGL / Windows)

Conway’s Game of Life をシンプルな構成で実装する学習用プロジェクトです。  
目的はモダン C++ と OpenGL の最小構成を通して、AI支援開発（GitHub Copilot）を実践することです。

## Features

- グリッド更新（B3/S23 ルール）
- 一時停止 / リセット / シード固定
- OpenGL + GLFW + GLEW による描画
- CMake でビルド可能（Windows / MSVC or MSYS2）

## Project Structure

```
core/      純粋ロジック（盤面更新）
render/    OpenGL描画
app/       メインループ・入力処理
tests/     ユニットテスト
.github/   Copilot 設定（開発方針・ルール）
```

## Build (Quick Start)

```bash
git clone https://github.com/konnononko/lifegame-modern-cpp.git
cd lifegame-modern-cpp
cmake -B build -S .
cmake --build build
build\Release\LifeGame.exe
```

## Development Notes

- C++23 / RAII / 例外非使用（constexpr, ranges, concepts, expected などモダン機能を適宜利用）
- core は標準ライブラリのみ（他層への依存禁止）
- 単一責任・短関数・テスト駆動を重視
- モダン、クリーン、ロバスト、シンプル、理解しやすい品質のよいコード。コード量は少なく。
- 詳細ルール: `.github/copilot-instructions.md`

## License

MIT

---

AIが提案するコードは、このREADMEと.github/copilot-instructions.mdの方針に従って簡潔・明快に実装されることを想定しています。
