########################################################################
# Fast Auxiliary Space Preconditioners (FASP) 
#
########################################################################

.PHONY: clean backup help

.DEFAULT: 
	@-make help

backup:
	@-rm -f faspsolver.zip
	@-zip -r faspsolver.zip README License base data test tutorial vs08 \
	                        doc/userguide.pdf
	
clean:
	@-rm -f *~

help:
	@echo "======================================================"
	@echo "||   Fast Auxiliary Space Preconditioners (FASP)    ||"
	@echo "======================================================"
	@echo "                                                      "
	@echo " make clean      : clean all ~ files                  "
	@echo " make backup     : generate a zip file for faspsolver "
	@echo " make help       : show this help screen              "
	@echo "                                                      "