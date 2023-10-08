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
#CXXFLAGS = -O3 -Wall -Wextra -std=c++17
CXXFLAGS =  -g -Wall -Wextra -std=c++17
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
artificiality_mf_qrfcm.out \
artificiality_qfcmf.out \
artificiality_fm.out \
mf.out \
mf_qrfcm.out \
qfcmf.out \
fm.out \
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
artificiality_mf.out : $(objects) src/recom.cxx \
main_recom/artificiality/mf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_mf_qrfcm.out : $(qrfcm) src/recom.cxx \
main_recom/artificiality/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_nmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/nmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
.out/artificiality_wnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/wnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_nmf_qrfcm.out : $(qrfcm) src/recom.cxx \
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
.out/artificiality_qfcwnmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@			
.out/artificiality_qfcmf.out : $(objects) src/recom.cxx \
main_recom/artificiality/qfcmf.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@		
.out/artificiality_fm.out : $(objects) src/recom.cxx \
main_recom/artificiality/fm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_fm_test.out : $(objects) src/recom.cxx \
main_recom/artificiality/fm-test.cxx 
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@


#推薦システム実データ
.out/mf.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/mf_qrfcm.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
nmf.out : $(objects) src/recom.cxx main_recom/nmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/wnmf.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/qfcmf.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@		
.out/fm.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	

.out/mf2.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf3.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@		
.out/mf4.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf5.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@		
.out/mf6.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf7.out : $(objects) src/recom.cxx main_recom/mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@				

.out/wnmf2.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/wnmf3.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/wnmf4.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/wnmf5.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/wnmf6.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/wnmf7.out : $(objects) src/recom.cxx main_recom/wnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@		

.out/mf_qrfcm2.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/mf_qrfcm3.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf_qrfcm4.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@				
.out/mf_qrfcm5.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/mf_qrfcm6.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/mf_qrfcm7.out : $(qrfcm) src/recom.cxx main_recom/mf_qrfcm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	

.out/qfcmf2.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcmf3.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcmf4.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcmf5.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/qfcmf6.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
.out/qfcmf7.out : $(objects) src/recom.cxx main_recom/qfcmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	

.out/qfcwnmf2.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf3.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf4.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf5.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf6.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/qfcwnmf7.out : $(objects) src/recom.cxx main_recom/qfcwnmf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	


.out/fm2.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/fm3.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/fm4.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/fm5.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/fm6.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	
.out/fm7.out : $(objects) src/recom.cxx main_recom/fm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@	

auc_calculation.out : $(objects) src/recom.cxx main_recom/auc_calculation.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
auc_calculation_mf.out : $(objects) src/recom.cxx main_recom/auc_calculation_mf.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@



clean :
	rm -f *.out
clean.o :
	rm -f .o/*.o
