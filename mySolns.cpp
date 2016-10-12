//Derek Boytim
//CSE 655
//HW 4
//mySolns

class Stmt {
public:
    virtual void execute() = 0;
};

class Stmts : public Stmt {
    Stmt* s1, s2;
public:
    Stmts {
	s1 = 0;
	s2 = 0;
    }
    
    ~Stmts {
	if (s1 != 0)
	    delete s1;
	if (s2 != 0)
	    delete s2;
    }
    
    void execute() {
	s1->execute();
	if (s2 != 0)
	    s2->execute();
    }
};

class Loop : public Stmt {
    Cond* cond;
    Stmt* stmt;
public:
    Loop {
	cond = 0;
	stmt = 0;
    }

    ~Loop {
	if (cond != 0)
	    delete cond;
	if (stmt != 0)
	    delete stmt;
    }

    void execute() {
	while (cond->execute())
	    stmt->execute();
    }
};

class If : public Stmt {
    Cond* cond;
    Stmt* stmt1, stmt2;
public:
    Loop {
	cond = 0;
	stmt1 = 0;
	stmt2 = 0;
    }

    ~Loop {
	if (cond != 0)
	    delete cond;
	if (stmt1 != 0)
	    delete stmt1;
	if (stmt2 != 0)
	    delete stmt2;
    }

    void execute() {
	if (cond->execute())
	    stmt1->execute();
	else if (stmt2 != 0)
	    stmt2->execute();
    }
};

class Assign : public Stmt {
    Id* id;
    Exp* exp;
public:
    Assign() {
	id = 0;
	exp = 0;
    }

    ~Assign() {
	if (id != 0)
	    delete id;
	if (exp != 0)
	    delete id;
    }

    void execute() {
	String s = id->execute();
	idValTable[s] = exp->execute();
    }
};

class In : public Stmt {
    Id* id;
public:
    In() {
	id = 0;
    }

    ~In() {
	if (id != 0)
	    delete id;
    }

    void execute() {
	cin >> id->value;
    }
};

class Out : public Stmt {
    Id* id;
public:
    Out() {
	id = 0;
    }

    ~Out() {
	if (id != 0)
	    delete id;
    }

    void execute() {
	cout << id->value;
    }
};
