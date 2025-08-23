<!-- README.md — HTML-styled for GPG_2020 -->

<h1 align="center" style="margin:24px 0 8px;">🚀 GPG_2020 — Space Arcade (Windows)</h1>
<p align="center" style="color:#586069; font-size:14px; margin:0 0 18px;">
  Небольшая космическая аркада под Windows. Поддерживает клавиатуру и геймпады (XInput: Xbox/PS).
</p>

<div align="center" style="margin-bottom:20px; display:inline-flex; gap:8px; flex-wrap:wrap;">
  <img alt="lang" src="https://img.shields.io/badge/lang-C%2B%2B%20%2B%20HLSL-1f6feb">
  <img alt="platform" src="https://img.shields.io/badge/platform-Windows-blue">
  <img alt="input" src="https://img.shields.io/badge/input-Keyboard%20%26%20Gamepad-43a047">
  <img alt="build" src="https://img.shields.io/badge/build-Visual%20Studio-5c2d91">
</div>

<hr style="margin: 12px 0 24px;"/>

<h2 id="about">🎮 О проекте</h2>
<p>
  <b>GPG_2020</b> — это «фановая» 2D-аркада с простым управлением и короткими динамичными раундами. 
  Репозиторий содержит Visual Studio-решение (<code>GPG_2020.sln</code>) и исходники игрового движка/сцен (классические сущности: игрок, противники, пули, фон).
</p>

<div align="center" style="margin: 18px 0 26px;">
  <img src="https://github.com/user-attachments/assets/5e7aec5f-b91d-4e6f-aa80-25d6382e62eb"
       alt="GPG_2020 gameplay placeholder"
       style="max-width: 980px; width: 100%; height: auto; border-radius: 14px; box-shadow: 0 10px 30px rgba(0,0,0,.22);" />
  <div style="font-size: 12px; color: #6a737d; margin-top: 8px;">
    Иллюстрация игрового процесса (плейсхолдер — замените на реальный скрин)
  </div>
</div>

<h2 id="video">🎥 Видео-разбор</h2>
<div align="center" style="margin: 10px 0 28px;">
  <iframe width="960" height="540"
          src="https://www.youtube.com/embed/4BgOpYNPx1Q"
          title="GPG_2020 — краткий разбор"
          frameborder="0"
          allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share"
          allowfullscreen
          style="max-width: 100%; border-radius: 12px; box-shadow: 0 10px 30px rgba(0,0,0,.2);">
  </iframe>
  <div style="font-size:12px; color:#6a737d; margin-top:8px;">
    Если встраивание недоступно — <a href="https://www.youtube.com/shorts/4BgOpYNPx1Q">смотрите ролик по ссылке</a>.
  </div>
</div>

<h2 id="features">✨ Особенности</h2>
<ul>
  <li><b>Arcade-core геймплей</b>: стрельба, уклонение, набор очков.</li>
  <li><b>Геймпады</b>: поддержка XInput (Xbox/PS-контроллеры), а также клавиатуры.</li>
  <li><b>Структура сцен</b>: титул, игра, завершение, фон, объекты (player/enemy/bullet/coin).</li>
  <li><b>Простая сборка</b>: Visual Studio-решение и готовые проектные файлы.</li>
</ul>

<hr style="margin: 16px 0 24px;"/>

<h2 id="quickstart">⚙️ Быстрый старт (Windows)</h2>
<ol>
  <li>Установите <b>Visual Studio 2019/2022</b> с компонентами «Desktop development with C++».</li>
  <li>Клонируйте репозиторий:
    <pre><code>git clone https://github.com/anabios13/GPG_2020.git
cd GPG_2020</code></pre>
  </li>
  <li>Откройте <code>GPG_2020.sln</code> (двойной клик или через VS → <em>Open a project or solution</em>).</li>
  <li>Выберите конфигурацию <code>Release</code> или <code>Debug</code>, платформу <code>x86</code> (если требуется) и соберите проект (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).</li>
  <li>Запустите игру (<kbd>F5</kbd> или <kbd>Ctrl</kbd>+<kbd>F5</kbd>).</li>
</ol>

<h3>📁 Ресурсы</h3>
<ul>
  <li>Папка <code>data/</code> предназначена для ассетов (шрифты, текстуры, аудио, если используются).</li>
  <li>Убедитесь, что исходные пути к ресурсам корректны для вашей конфигурации (Debug/Release).</li>
</ul>

<h2 id="controls">🎯 Управление</h2>
<div style="display:grid; grid-template-columns: repeat(auto-fit, minmax(240px, 1fr)); gap:10px;">
  <div>
    <h4 style="margin:8px 0;">Клавиатура</h4>
    <ul>
      <li>Передвижение — <b>W/A/S/D</b> или стрелки</li>
      <li>Огонь/Действие — <b>Space</b> / <b>Enter</b></li>
      <li>Пауза — <b>Esc</b></li>
    </ul>
  </div>
  <div>
    <h4 style="margin:8px 0;">Геймпад (XInput)</h4>
    <ul>
      <li>Передвижение — <b>Left Stick / D-Pad</b></li>
      <li>Огонь — <b>A / X</b> (в зависимости от контроллера)</li>
      <li>Пауза/Back — <b>Start/Back</b></li>
    </ul>
  </div>
</div>
<p style="font-size:12px; color:#6a737d; margin-top:4px;">
  Примечание: раскладка может отличаться — при необходимости поправьте в коде обработки ввода.
</p>

<hr style="margin: 16px 0 24px;"/>

<h2 id="tech">🧩 Технические детали</h2>
<ul>
  <li>Язык: <b>C++</b> (основная логика), <b>HLSL</b> (шейдеры, если задействованы).</li>
  <li>Архитектура: отдельные задачи/сцены (<code>Task_*.cpp</code>) и базовый игровой движок (<code>GameEngine_*.cpp</code>).</li>
  <li>Проектные файлы: <code>GPG_2020.vcxproj</code>, фильтры, решение <code>.sln</code>.</li>
</ul>

<h2 id="dev">👩‍💻 Подсказки разработчикам</h2>
<ul>
  <li>Сборка лучше всего проходит в том же toolset, под который создавался проект (при несовпадении — Visual Studio предложит апгрейд).</li>
  <li>Если используете геймпад: убедитесь, что XInput DLL доступна системе (обычно входит в состав Windows 10/11).</li>
  <li>Папка <code>data/</code> должна быть доступна исполняемому файлу в рабочей директории (скопируйте ассеты в выходную папку при необходимости — настройка <i>Post-build event</i>).</li>
</ul>

<hr style="margin: 16px 0 24px;"/>

<p align="center" style="font-size:13px; color:#6a737d;">
  Игра для души и для практики: простой код, быстрая сборка, понятная архитектура.
</p>

