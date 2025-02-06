curl -L -o assets/assets.zip --url https://github.com/kuukitenshi/Assets-Arcane/archive/refs/heads/master.zip
tar -xf assets\assets.zip -C assets --strip-components=1 
del assets\assets.zip

cmake -Bbuild -DCMAKE_BUILD_TYPE=Release .
cmake --build build --config Release

del ..\release\unit.exe