dataフォルダ
{
ratings_data2.txt
ダウンロードしたオリジナルデータ
ユーザ番号，アイテム番号，評価値，の順に並んでいる

epinioons_oridata.txt
オリジナルデータはユーザ番号，アイテム番号を-1したもの
ユーザ番号，アイテム番号，評価値，の順に並んでいる

ratings_rowmajor.txt
データ整形に必要
ユーザ番号，アイテム番号，評価値，の順に並んでいる

ratings_colmajor.txt
データ整形に必要
アイテム番号，ユーザ番号，評価値，の順に並んでいる
}

epinons_make.cxx
ratings_rowmajor.txtを作るためのプログラム
(プログラムの実行にはEigenライブラリが必要です)

epinons.cxx
データを削るプログラム
(プログラムの実行にはEigenライブラリが必要です)

s_epinons.cxx
データをスパース表記に変えるプログラム，コマンドライン引数にデータ名，要素数，ユーザ数が必要

epinions_2088_1381.txt
データ整形後のデータ

sparse_epinions_2088_1381.txt
完成したスパースデータ

以下の順に実行する
epinons_make.cxx

コマンド awk '{print $2" "$1" "$3}' data/ratings_rowmajor.txt | sort -k1n > data/ratings_colmajor.txt

epinons.cxx

s_epinons.cxx
