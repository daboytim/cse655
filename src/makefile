#Derek Boytim
#CSE 655
#5-3-2012
#lab1
#makefile

SRC=tokenizer.h program.h declseq.h stmtseq.h decl.h idlist.h stmt.h \
	assign.h if.h loop.h input.h output.h cond.h comp.h exp.h fac.h \
	op.h id.h int.h ifimpl.h loopimpl.h inputimpl.h outputimpl.h \
	opimpl.h facimpl.h

interpreter: interpreter.o
	g++ -o interpreter interpreter.o

interpreter.o: interpreter.cpp $(SRC)
	g++ -c interpreter.cpp

debug: $(SRC)
	g++ -g -o interpreter interpreter.cpp

clean:
	rm interpreter.o interpreter
