files=("mf.out" "wnmf.out" "qfcmf.out" "qfcwnmf.out" "fm.out" ) #
# 制御用のFIFOファイルを作成
# 2つのコアで並列処理を実行 #
for file in "${files[@]}";  #
do #
{
for ((i=2; i<7; i++)) #
do  #
  { #
    make ".out/$file" #
    taskset -c $((i - 2)) ".out/$file" 1 5 "${i}" "${i}" #
  } & #
done #
} ;
done #

# 全てのジョブが完了するまで待機
wait #



#nohup ./artificiality_mf.out 1 4 2 9 > log/mf-0919.log & #

# make .out/mf.out #
# make .out/mf2.out #
# make .out/mf3.out #
# make .out/mf4.out #
# make .out/mf5.out #
# make .out/mf6.out #
# make .out/mf7.out #
# make .out/wnmf.out #
# make .out/wnmf2.out #
# make .out/wnmf3.out #
# make .out/wnmf4.out #
# make .out/wnmf5.out #
# make .out/wnmf6.out #
# make .out/wnmf7.out #
# make .out/mf_qrfcm.out #
# make .out/mf_qrfcm2.out #
# make .out/mf_qrfcm3.out #
# make .out/mf_qrfcm4.out #
# make .out/mf_qrfcm5.out #
# make .out/mf_qrfcm6.out #
# make .out/mf_qrfcm7.out #

# (./.out/mf.out 1 5 8 8 && ./.out/wnmf.out 1 5 2 2 && ./.out/mf_qrfcm.out 1 5 2 8 8 8 1000 1000 1.1 1.1) & #
# (./.out/mf2.out 1 5 7 7 && ./.out/wnmf2.out 1 5 3 3 && ./.out/mf_qrfcm2.out 1 5 2 8 7 7 1000 1000 1.1 1.1)  & #
# (./.out/mf3.out 1 5 6 6 && ./.out/wnmf3.out 1 5 4 4 && ./.out/mf_qrfcm3.out 1 5 2 8 6 6 1000 1000 1.1 1.1) & #
# (./.out/mf4.out 1 5 5 5 && ./.out/wnmf4.out 1 5 5 5 && ./.out/mf_qrfcm4.out 1 5 2 8 5 5 1000 1000 1.1 1.1)  & #
# (./.out/mf5.out 1 5 4 4 && ./.out/wnmf5.out 1 5 6 6 && ./.out/mf_qrfcm5.out 1 5 2 8 4 4 1000 1000 1.1 1.1)  & #
# (./.out/mf6.out 1 5 3 3 && ./.out/wnmf6.out 1 5 7 7 && ./.out/mf_qrfcm6.out 1 5 2 8 3 3 1000 1000 1.1 1.1) & #
# (./.out/mf7.out 1 5 2 2 && ./.out/wnmf7.out 1 5 8 8 && ./.out/mf_qrfcm7.out 1 5 2 8 2 2 1000 1000 1.1 1.1) & #
