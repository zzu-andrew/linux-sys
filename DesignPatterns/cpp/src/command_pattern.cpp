//
// Created by andrew on 2020/11/23.
//
#include <iostream>
#include <list>

using namespace std;

class Doctor {
public:
    void treatEye() {
        cout << "treat eye" << endl;
    }

    void treatNose() {
        cout << "treat nose" << endl;
    }
};

class Command {
public:
    virtual void treat() = 0;

    virtual ~Command() = default;
};

class CommandTreatEye : public Command {
public:
    explicit CommandTreatEye(Doctor *doctor) {
        m_doctor = doctor;
    }

    void treat() override {
        m_doctor->treatEye();
    }

private:
    Doctor *m_doctor;
};


class CommandTreatNose : public Command {
public:
    explicit CommandTreatNose(Doctor *doctor) {
        m_doctor = doctor;
    }

    void treat() override {
        m_doctor->treatNose();
    }

private:
    Doctor *m_doctor;
};

//小护士
class BeautyNurse {
public:
    explicit BeautyNurse(Command *command) {
        this->command = command;
    }

    void SubmittedCase() { // 提交病历 下单命令
        command->treat();
    }

private:
    Command *command;
};

class HeadNurse {
public:
    HeadNurse() {
        m_list.clear();
    }

    void setCommand(Command *command) {
        m_list.push_back(command);
    }

    void SubmittedCase() { // 提交命令
        for (auto & it : m_list) {
            it->treat();
        }
    }

private:
    list<Command *> m_list;
};


void nurseCommand() {
    BeautyNurse *beautyNurse = nullptr;
    Doctor *doctor = nullptr;
    Command *command = nullptr;

    doctor = new Doctor;
//
    command = new CommandTreatNose(doctor);
    beautyNurse = new BeautyNurse(command);
    beautyNurse->SubmittedCase();

    delete doctor;
    delete command;
    delete beautyNurse;
}

void headNurseCommand() {
//    护士长 提交病历  给以上看病
    HeadNurse *headNurse = NULL;
    Doctor * doctor = NULL;
    Command *command1 = NULL;
    Command *command2 = NULL;

    doctor = new Doctor;
    command1 = new CommandTreatEye(doctor);
    command2 = new CommandTreatNose(doctor);

    headNurse = new HeadNurse;
    headNurse->setCommand(command1);
    headNurse->setCommand(command2);

    headNurse->SubmittedCase(); // 护士长  批量下单命令

    delete doctor;
    delete command1;
    delete command2;
    delete headNurse;
}


int main(int argc, char *argv[]) {

    //   通过一个命令  调用医生实现病的治疗 命令的执行部分实现
    /* Doctor *dcotor = new Doctor;
     CommandTreatEye *commandTreatEye = new CommandTreatEye(dcotor);
     commandTreatEye->treat();
     delete commandTreatEye;
     delete dcotor;*/

    //
    nurseCommand();
    headNurseCommand();

    return 0;
}
