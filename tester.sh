#!/bin/bash

# maps klasöründeki ve alt klasörlerdeki tüm .cub dosyalarını bul
find maps -type f -name "*.cub" | while read -r file; do
    echo "==== Çalıştırılıyor: $file ===="
    ./cub3D "$file"
    echo ""
done
