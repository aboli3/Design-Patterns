#include <iostream>
#include <string>

// Forward declarations
class Document;
class DraftState;
class ReviewState;
class ApprovedState;
class RejectedState;

// State Interface
class State {
protected:
    Document* document;

public:
    void setDocument(Document* doc) {
        document = doc;
    }

    virtual void draft() = 0;
    virtual void review() = 0;
    virtual void approve() = 0;
    virtual void reject() = 0;
    virtual std::string getStateName() = 0;
    virtual ~State() = default;
};

// Document class (Context)
class Document {
private:
    State* currentState;
    std::string documentName;

public:
    Document(const std::string& name) : documentName(name) {
        currentState = nullptr;
    }

    void setState(State* state) {
        if (currentState != nullptr) {
            delete currentState;
        }
        currentState = state;
        currentState->setDocument(this);
    }

    void draft() {
        currentState->draft();
    }

    void review() {
        currentState->review();
    }

    void approve() {
        currentState->approve();
    }

    void reject() {
        currentState->reject();
    }

    std::string getCurrentState() {
        return currentState->getStateName();
    }

    std::string getName() const {
        return documentName;
    }

    ~Document() {
        delete currentState;
    }
};

// Declare all state classes first
class DraftState : public State {
public:
    void draft() override;
    void review() override;
    void approve() override;
    void reject() override;
    std::string getStateName() override;
};

class ReviewState : public State {
public:
    void draft() override;
    void review() override;
    void approve() override;
    void reject() override;
    std::string getStateName() override;
};

class ApprovedState : public State {
public:
    void draft() override;
    void review() override;
    void approve() override;
    void reject() override;
    std::string getStateName() override;
};

class RejectedState : public State {
public:
    void draft() override;
    void review() override;
    void approve() override;
    void reject() override;
    std::string getStateName() override;
};

// Now implement all the state methods
void DraftState::draft() {
    std::cout << "Document [" << document->getName() << "] is already in Draft state\n";
}

void DraftState::review() {
    std::cout << "Document [" << document->getName() << "] sent for review\n";
    document->setState(new ReviewState());
}

void DraftState::approve() {
    std::cout << "Cannot approve document in Draft state\n";
}

void DraftState::reject() {
    std::cout << "Cannot reject document in Draft state\n";
}

std::string DraftState::getStateName() {
    return "Draft";
}

void ReviewState::draft() {
    std::cout << "Document [" << document->getName() << "] moved back to Draft\n";
    document->setState(new DraftState());
}

void ReviewState::review() {
    std::cout << "Document [" << document->getName() << "] is already under review\n";
}

void ReviewState::approve() {
    std::cout << "Document [" << document->getName() << "] approved\n";
    document->setState(new ApprovedState());
}

void ReviewState::reject() {
    std::cout << "Document [" << document->getName() << "] rejected\n";
    document->setState(new RejectedState());
}

std::string ReviewState::getStateName() {
    return "Under Review";
}

void ApprovedState::draft() {
    std::cout << "Cannot modify approved document\n";
}

void ApprovedState::review() {
    std::cout << "Cannot review approved document\n";
}

void ApprovedState::approve() {
    std::cout << "Document is already approved\n";
}

void ApprovedState::reject() {
    std::cout << "Cannot reject approved document\n";
}

std::string ApprovedState::getStateName() {
    return "Approved";
}

void RejectedState::draft() {
    std::cout << "Document [" << document->getName() << "] moved back to Draft\n";
    document->setState(new DraftState());
}

void RejectedState::review() {
    std::cout << "Cannot review rejected document\n";
}

void RejectedState::approve() {
    std::cout << "Cannot approve rejected document\n";
}

void RejectedState::reject() {
    std::cout << "Document is already rejected\n";
}

std::string RejectedState::getStateName() {
    return "Rejected";
}

int main() {
    // Create a new document
    Document doc("Project Proposal");
    
    // Set initial state
    doc.setState(new DraftState());

    // Test state transitions
    std::cout << "Current State: " << doc.getCurrentState() << "\n\n";

    doc.review();  // Draft -> Review
    std::cout << "Current State: " << doc.getCurrentState() << "\n\n";

    doc.approve(); // Review -> Approved
    std::cout << "Current State: " << doc.getCurrentState() << "\n\n";

    // Try invalid transitions
    doc.draft();   // Cannot modify approved document
    std::cout << "Current State: " << doc.getCurrentState() << "\n\n";

    // Create another document to test rejection
    Document doc2("Budget Report");
    doc2.setState(new DraftState());
    
    doc2.review();  // Draft -> Review
    doc2.reject();  // Review -> Rejected
    std::cout << "Document 2 Current State: " << doc2.getCurrentState() << "\n\n";

    // Can move rejected document back to draft
    doc2.draft();   // Rejected -> Draft
    std::cout << "Document 2 Current State: " << doc2.getCurrentState() << "\n";

    return 0;
}
