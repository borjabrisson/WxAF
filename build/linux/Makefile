OBJS="."

include ./build/linux-config.gcc

.PHONY : clean	no-temporal
all:  WxAF_base app frameContainer custom
	g++  wx.cpp -o gui.out ${Build}/*.o ${wxFALGS} ${MySQLFLAGS}
# 	rm *.o *.d
frameContainer:
	g++  ${wxFALGS} ${CPPFLAGS} -MF ${Build}/"frameContainer.d" -MT ${Build}/"frameContainer.d" ${MySQLFLAGS} -o ${Build}/"frameContainer.o" frameContainer.cpp
app:
	g++  ${wxFALGS} ${CPPFLAGS} -MF ${Build}/"MyApp.d" -MT ${Build}/"MyApp.d" ${MySQLFLAGS} -o ${Build}/"MyApp.o" MyApp.cpp
WxAF_base:
	make --file=./Basefile.gcc
custom:
	make --file=./Customfile.gcc
clean:
	if [ "$$(ls ${Build} | grep -F .o )" ]; then rm ${Build}/*.o; fi
	if [ "$$(ls ${Build} | grep -F .d )" ]; then rm ${Build}/*.d; fi
# 	rm *.o *.d
no-temporal:
	echo [${MODULOS}]*
#          rm base/*.cpp~ base/*.h~ conector/*.cpp~ conector/*.h~ base/*.cpp~ base/*.h~


qwert:
	for number in 1 2 3 4 ; do \
		echo $$number ; \
	done

