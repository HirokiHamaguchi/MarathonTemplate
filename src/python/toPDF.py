# https://qiita.com/daikan_murata/items/e1c38db8b41d141f12d8

import os
import img2pdf
from PIL import Image


pdf_file_name = f"doc/output.pdf"
png_Folder = f"img/vis/"  # 画像フォルダ
extension = ".png"  # 拡張子がPNGのものを対象

with open(pdf_file_name, "wb") as f:
    # 画像フォルダの中にあるPNGファイルを取得し配列に追加、バイナリ形式でファイルに書き込む
    f.write(img2pdf.convert(
        [Image.open(png_Folder+j).filename
         for j in sorted([j for j in os.listdir(png_Folder) if j.endswith(extension)])
         ]
    ))
