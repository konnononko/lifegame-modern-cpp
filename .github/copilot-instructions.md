# Copilot Instructions (LifeGame, C++23)

## Goals / Scope

- 目的: モダンC++23 + OpenGL の最小構成で Life を実装し、読みやすく拡張しやすいコードを示す
- 範囲: B3/S23、512×512想定、Pause/Reset/Seed、ウィンドウ内描画（固定サイズウィンドウ）
- 非範囲: 複雑GUI、ファイルI/O、並列最適化、DirectX（将来検討）
- 将来拡張の可能性あり: ウィンドウリサイズ対応、ImGui（Dear ImGui）による簡易GUI

## Environment

- Windows 11 / CMake / Ninja 推奨
- MSVC または MSYS2(UCRT64) の GCC/Clang
- 依存: OpenGL, GLFW, GLEW（必要に応じ GLM）

## Layout & Dependencies

```
core/    STLのみ（入出力やGL禁止）
render/  GLFW/GLEW 初期化 + RGBA8テクスチャ更新 + ウィンドウ描画（固定解像度）
app/     main とイベントループ・入力
tests/   最小ユニットテスト
```
依存方向: app → {core,render}。core ←× render の参照禁止。
将来的にリサイズイベント対応や ImGui オーバーレイ追加を想定し、`render` 層の責務を明確に分離する。

## Coding Rules

- モダン、クリーン、ロバスト、シンプル、理解しやすい品質のよいコード。コード量は少なく。
- C++23 / RAII / 例外非使用（`std::expected<T,E>` 推奨）, `noexcept` 明示
- 短関数・単一責任、前方宣言と小さなヘッダ、循環依存禁止
- `const` を積極使用、未定義動作の恐れがあるビット操作は避ける
- フォーマットは .clang-format / .editorconfig に従う（自動整形前提）

## Naming Conventions

- Functions / variables: `snake_case`
  - 例: `step_grid()`, `update_cells()`, `draw_frame()`
- Types (class / struct / enum): `PascalCase`
  - 例: `Grid`, `RendererGL`, `CreateInfo`
- Constants / constexpr / enum values: `UPPER_SNAKE_CASE`
  - 例: `DEFAULT_WIDTH`, `MAX_CELLS`, `RULE_B3S23`
- Namespaces: `lowercase`（1語）
  - 例: `life`, `render`
- Private members: `_` サフィックス
  - 例: `width_`, `height_`, `cells_`
- File names: `snake_case`（クラス名を含めない）
  - ソース: `.cpp`
  - ヘッダ: `.hpp`（C++専用ヘッダとして`.h`は使用しない）
  - 例: `grid.cpp`, `renderer_gl.cpp`
- Header guards: `#pragma once` 形式
- Acronyms: 型名では頭字語を大文字維持（`RendererGL`）、関数・変数では小文字化（`load_gl_resources()`）

命名の目的は「読みやすく予測しやすいコード」を書くこと。  
同じ概念には常に同じ単語を使い、略語や単語順を変えない。

## Public API（主導）

```cpp
// core/life.hpp
namespace life {
class Grid {
public:
  // 事前条件: w>0 && h>0（満たさない場合はデバッグ時に assert）
  Grid(int w,int h,std::uint64_t seed) noexcept;
  void step() noexcept; // B3/S23
  void randomize(std::uint64_t seed) noexcept;
  int width() const noexcept; 
  int height() const noexcept;
  // 0/1, row-major。コンテナ非依存で受け渡しできるように span を返す
  std::span<const std::uint8_t> cells() const noexcept;
};
}
````

## Testing (minimum)

- 等価クラス: 全死 / 全生 / ブロック / ブリンカー / 縞
- 境界値: 1×1, 1×N, 大きめ N×N（必要ならスキップ可）
- 仕様確認: 端セルは盤外を「死」とみなすこと（非トーラス）。寸法が0以下は生成不可。

## Anti-Patterns

- 例外での制御、グローバル可変、core→render 逆依存、巨大単一ファイル、無根拠な最適化

## Chat Prompts（短文例）

- 「このREADME/指示に従い、`tests/test_life.cpp` にブロック/ブリンカー/全死の赤テストを追加」
- 「`core/life.cpp` の `step()` を最小で実装（分岐最小化）。テストを緑にするパッチをdiffで」
- 「GLFW/GLEW初期化と RGBA8 テクスチャ更新、全画面クアッド描画を `render/` に分離して生成」
