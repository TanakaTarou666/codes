# https://github.com/ntyaan/some-datasets
# $ make (vectorクラス等の中間ファイル作成、-Bで強制コンパイル) 
# $ make ターゲット(.out)で実行ファイルコンパイル
# ---推薦システム---
# 実データ一覧 
# 名前		:マクロ名	
# BookCrossing	:BOOK		:1091ユーザ2248アイテム35179要素
# MovieLens100K	:MOVIE		:874ユーザ598アイテム82275要素
# MovieLens1M	:MOVIE		:905ユーザ684アイテム277546要素
# MovieLens10M	:MOVIE		:1299ユーザ1695アイテム1022610要素
# Jester		:JESTER		:2916ユーザ140アイテム373338要素
# Libimseti		:LIBIMSETI	:866ユーザ1156アイテム400955要素
# Epinions		:EPINIONS	:1022ユーザ835アイテム42808要素
# Sushi			:SUSHI		:5000ユーザ100アイテム50000要素
# Sushi_9		:SUSHI_NINE	:3007ユーザ52アイテム28184要素
# Netflix		:NETFLIX	:542ユーザ4495アイテム1291999要素
# 実データの場合:
# $ make ターゲット data=マクロ名
# 例(klfcsをBookCrossingに適用する場合):
# $ make rklfcs.out data=BOOK
# クラスの呼び出し等デバグしたいとき
# $ make ターゲット data=マクロ名 class=1
# 人工データの場合:
# $ make ターゲット
CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++17
#CXXFLAGS =  -g -Wall -Wextra -std=c++17 #debug用
# CXXFLAGS = -O0 -Wall -Wextra -std=c++17 -g  # debug用(計算時間がかなり増加するので注意)
FS = -lstdc++fs
objects = .o/vector.o .o/svector.o .o/matrix.o .o/smatrix.o .o/vector3d.o
mpbmf = $(objects) .o/vector3d.o
qfcm = $(objects) .o/hcm.o .o/hcma.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o
klfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/klfcm.o .o/klfcs.o
bfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/bfcm.o .o/bfcs.o
qfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o .o/qfcs.o
klfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o .o/klfcm.o .o/klfccm.o
bfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o .o/bfcm.o .o/bfccm.o
qfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o .o/qfccm.o
klfccmm = $(klfccm) .o/hccmm.o .o/klfccmm.o
bfccmm = $(bfccm) .o/hccmm.o .o/bfccmm.o
qfccmm = $(qfccm) .o/hccmm.o .o/qfccmm.o
epcs = $(klfcs) .o/pcm.o .o/epcs.o
erfcm = $(objects) .o/hcm.o .o/hcma.o .o/klfcm.o .o/rfcm.o .o/erfcm.o
brfcm = $(objects) .o/hcm.o .o/hcma.o .o/bfcm.o .o/rfcm.o .o/brfcm.o
qrfcm = $(objects) .o/hcm.o .o/hcma.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o .o/rfcm.o .o/qrfcm.o

method_all = $(all) \
$(qfcm) \
$(klfcs) $(bfcs) $(qfcs) \
$(klfccm) $(bfccm) $(qfccm) \
$(klfccmm) $(bfccmm) $(qfccmm) \
$(epcs) $(erfcm) $(brfcm) $(qrfcm) \
artificiality_grouplens.out \
artificiality_mf.out \
artificiality_mf_qfcs.out \
artificiality_mf_qrfcm.out \
artificiality_qfcmf.out \
artificiality_mpbmf.out \
artificiality_fm.out \
artificiality_klfcs.out \
artificiality_bfcs.out \
artificiality_qfcs.out \
artificiality_klfccm.out \
artificiality_bfccm.out \
artificiality_qfccm.out \
artificiality_klfccmm.out \
artificiality_qfccmm.out \
artificiality_epcs.out \
grouplens.out \
mf.out \
mf_qfcs.out \
mf_qrfcm.out \
qfcmf.out \
mpbmf.out \
fm.out \
qfcm.out \
klfcs.out \
bfcs.out \
qfcs.out \
klfccm.out \
bfccm.out \
qfccm.out \
klfccmm.out \
bfccmm.out \
qfccmm.out \
epcs.out \
erfcm.out \
brfcm.out \
qrfcm.out \
clustering_artificiality_klfcs.out \
clustering_artificiality_bfcs.out \
clustering_artificiality_qfcs.out \
clustering_artificiality_klfccm.out \
clustering_artificiality_bfccm.out \
clustering_artificiality_qfccm.out \
clustering_artificiality_klfccmm.out \
clustering_artificiality_bfccmm.out \
clustering_artificiality_qfccmm.out \
clustering_artificiality_epcs.out \
clustering_klfcs.out \
clustering_bfcs.out \
clustering_qfcs.out \
clustering_klfccm.out \
clustering_bfccm.out \
clustering_qfccm.out \
clustering_klfccmm.out \
clustering_bfccmm.out \
clustering_qfccmm.out \
auc_calculation.out \
auc_calculation_mf.out \

ifdef data
	DATASET=-D$(data) 
endif
ifdef class
	MACRO=-DCHECK_CLASS 
endif

all : $(objects) 

method_all : $(method_all)

.o/vector.o : src/vector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/svector.o : src/sparseVector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/matrix.o : src/matrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/smatrix.o : src/sparseMatrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/vector3d.o : src/vector3d.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcm.o : src/hcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcma.o : src/hcma.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcs.o : src/hcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hccm.o : src/hccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hccmm.o : src/hccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/pcm.o : src/pcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/rfcm.o : src/rfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfcm.o : src/klfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfcs.o : src/klfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcm.o : src/bfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcs.o : src/bfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcm.o : src/qfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcs.o : src/qfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfccm.o : src/klfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfccm.o : src/bfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfccm.o : src/qfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfccmm.o : src/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfccmm.o : src/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfccmm.o : src/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/epcs.o : src/epcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/erfcm.o : src/erfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/brfcm.o : src/brfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qrfcm.o : src/qrfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@

#推薦システム人工データ
artificiality_grouplens.out : $(objects) src/recom.cxx \
main_recom/artificiality/grouplens.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_mf.out : $(objects) src/recom.cxx \
main_recom/artificiality/mf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_mf_qfcs.out : $(qfcs) src/recom.cxx \
main_recom/artificiality/mf_qfcs.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_mf_qrfcm.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_mf_qrfcm_2.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_nmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/nmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_wnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/wnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_nmf_qrfcm.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/nmf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@	
artificiality_wnmf_qrfcm.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/wnmf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_nmf_qrfcm_2.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/nmf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@	
artificiality_bfcnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/bfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfcnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/qfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@	
artificiality_qfcwnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@				
artificiality_tfcnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcfm_als.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcfm_als.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@			
artificiality_tfcnmf-2.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcnmf-3.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcnmf-4.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcwnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcwnmf-2.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcwnmf-3.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcwnmf-4.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@	
artificiality_qfcmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/qfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcmf-2.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-3.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-4.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-5.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-6.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-7.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-8.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-1.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
artificiality_tfcmf-2-2.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-3.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-4.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-5.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-6.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-7.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_tfcmf-2-8.out : $(objects) src/recom.cxx \
main_recom/artificiality/tfcmf-2.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@	
artificiality_mpbmf.out : $(mpbmf) src/recom.cxx \
main_recom/artificiality/mpbmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_fm.out : $(objects) src/recom.cxx \
main_recom/artificiality/fm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_fm_test.out : $(objects) src/recom.cxx \
main_recom/artificiality/fm-test.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfcm.out : $(qfcm) src/recom.cxx \
main_recom/artificiality/qfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfcs.out : $(klfcs) src/recom.cxx \
main_recom/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfcs.out : $(bfcs) src/recom.cxx \
main_recom/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfcs.out : $(qfcs) src/recom.cxx \
main_recom/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccm.out : $(klfccm) src/recom.cxx \
main_recom/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfccm.out : $(bfccm) src/recom.cxx \
main_recom/artificiality/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccm.out : $(qfccm) src/recom.cxx \
main_recom/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccmm.out : $(klfccmm) src/recom.cxx \
main_recom/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfccmm.out : $(bfccmm) src/recom.cxx \
main_recom/artificiality/bfccmm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccmm.out : $(qfccmm) src/recom.cxx \
main_recom/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_epcs.out : $(epcs) src/recom.cxx \
main_recom/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_erfcm.out : $(erfcm) src/recom.cxx \
main_recom/artificiality/erfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_brfcm.out : $(brfcm) src/recom.cxx \
main_recom/artificiality/brfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qrfcm.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@

#推薦システム実データ
grouplens.out : $(objects) src/recom.cxx main_recom/grouplens.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
mf.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
mf_qfcs.out : $(qfcs) src/recom.cxx main_recom/mf_qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
mf_qrfcm.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
mf_qrfcm2.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf_qrfcm.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
wnmf_qrfcm.out : $(qrfcm) src/recom.cxx main_recom/wnmf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/wnmf_qrfcm.out : $(qrfcm) src/recom.cxx main_recom/wnmf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
qfcm.out : $(qfcm) src/recom.cxx main_recom/qfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfcs.out : $(bfcs) src/recom.cxx main_recom/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfcs.out : $(klfcs) src/recom.cxx main_recom/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfcs.out : $(qfcs) src/recom.cxx main_recom/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccm.out : $(bfccm) src/recom.cxx main_recom/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccm.out : $(klfccm) src/recom.cxx main_recom/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccm.out : $(qfccm) src/recom.cxx main_recom/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccmm.out : $(klfccmm) src/recom.cxx main_recom/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccmm.out : $(bfccmm) src/recom.cxx main_recom/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccmm.out : $(qfccmm) src/recom.cxx main_recom/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
epcs.out : $(epcs) src/recom.cxx main_recom/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
brfcm.out : $(brfcm) src/recom.cxx main_recom/brfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
erfcm.out : $(erfcm) src/recom.cxx main_recom/erfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qrfcm.out : $(qrfcm) src/recom.cxx main_recom/qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
auc_calculation.out : $(objects) src/recom.cxx main_recom/auc_calculation.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
auc_calculation_mf.out : $(objects) src/recom.cxx main_recom/auc_calculation_mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@


#クラスタリング人工データ
clustering_artificiality_klfcs.out : $(klfcs) \
main_clustering/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_bfcs.out : $(bfcs) \
main_clustering/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_qfcs.out : $(qfcs) \
main_clustering/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_klfccm.out : $(klfccm) \
main_clustering/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccm.out : $(bfccm) \
main_clustering/artificiality/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccm.out : $(qfccm) \
main_clustering/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_klfccmm.out : $(klfccmm) \
main_clustering/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccmm.out : $(bfccmm) \
main_clustering/artificiality/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccmm.out : $(qfccmm) \
main_clustering/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_epcs.out : $(epcs) \
main_clustering/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@

#クラスタリング実データ
clustering_klfcs.out : $(klfcs) main_clustering/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfcs.out : $(bfcs) main_clustering/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfcs.out : $(qfcs) main_clustering/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccm.out : $(klfccm) main_clustering/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccm.out : $(bfccm) main_clustering/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccm.out : $(qfccm) main_clustering/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccmm.out : $(klfccmm) main_clustering/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccmm.out : $(bfccmm) main_clustering/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccmm.out : $(qfccmm) main_clustering/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@

#クラスタリング実データ
init_centers_clustering_klfcs.out : $(klfcs) \
main_clustering/initialize_centers/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_bfcs.out : $(bfcs) \
main_clustering/initialize_centers/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_qfcs.out : $(qfcs) \
main_clustering/initialize_centers/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_klfccm.out : $(klfccm) \
main_clustering/initialize_centers/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_bfccm.out : $(bfccm) \
main_clustering/initialize_centers/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_qfccm.out : $(qfccm) \
main_clustering/initialize_centers/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_klfccmm.out : $(klfccmm) \
main_clustering/initialize_centers/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_bfccmm.out : $(bfccmm) \
main_clustering/initialize_centers/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
init_centers_clustering_qfccmm.out : $(qfccmm) \
main_clustering/initialize_centers/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@

clean :
	rm -f *.out
clean.o :
	rm -f .o/*.o
