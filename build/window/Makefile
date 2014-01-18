OBJS="."

include build/window/general.gcc
include build/linux-config.gcc

.PHONY : clean	no-temporal
all:  WxAF_base app.o frameContainer.o custom
	g++  -o gui.exe ${Build}/*.o -I$(WXWIN)\include  ${APP_FLAGS} wx.cpp
# 	rm *.o *.d
	
frameContainer.o: frameContainer.cpp
	g++    ${wxAF_CXXFLAGS} ${CPPFLAGS} -MT${Build}/$@ -MF${Build}/$@.d -MD -MP  -o ${Build}/$@ $<

app.o: MyApp.cpp
	g++    ${wxAF_CXXFLAGS} ${CPPFLAGS} -MT${Build}/$@ -MF${Build}/$@.d -MD -MP  -o ${Build}/$@ $<
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
exec:
	g++  -o gui.exe ${Build}/*.o  -I'C:\wxWidgets-2.8.10\include'  -I$(WXWIN)\include\wx ${APP_FLAGS} wx.cpp

qwert:
	for number in 1 2 3 4 ; do \
		echo $$number ; \
	done

