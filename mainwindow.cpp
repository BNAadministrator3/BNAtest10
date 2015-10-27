#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QFileDialog>
#include <QMessageBox>
#include <QtGlobal>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using  std::string;
extern QString file_name_transimit;
bool individual_metrics=0;
bool average_ordinary=0;
bool average_fisher=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 // this->setWindowFlags(windowFlags()| Qt::WindowMaximizeButtonHint);
  // this->setWindowFlags( windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint );
    connect(this,SIGNAL(mySignalMtoS()),&w1,SLOT(on_pushButtonLoad_clicked()));
    connect(&w1,SIGNAL(mySignalStoM()),this,SLOT(on_pushButtonLoad_clicked()));
    //这种connect的方式我也是醉了！！！！！
    connect(this,SIGNAL(mySignalMclr()),this,SLOT(clearscreen()));

     connect(this,SIGNAL(mySignalMgrayBoxCUCorMat(bool)),this,SLOT(on_checkCUCorMat_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxLp(bool)),this,SLOT(on_checkLp_clicked(bool)));
    // connect(this,SIGNAL(mySignalMgrayBoxCUBFS_Lp(bool)),this,SLOT(on_checkCUBFS_Lp_clicked(bool)));
    // connect(this,SIGNAL(mySignalMgrayBoxBFS_MulCPU(bool)),this,SLOT(on_checkBFS_MulCPU_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxCP(bool)),this,SLOT(on_checkCP_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxDegree(bool)),this,SLOT(on_checkDegree_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxCUBC(bool)),this,SLOT(on_checkCUBC_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxCUEC(bool)),this,SLOT(on_checkCUEC_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxL_Modularity(bool)),this,SLOT(on_checkL_Modularity_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxPC_CPU(bool)),this,SLOT(on_checkPC_CPU_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxConvertNII(bool)),this,SLOT(on_checkConvertNII_clicked(bool)));

     connect(this,SIGNAL(mySignalMgrayBoxLp_NodalMetrics(bool)),this,SLOT(on_checkLp_NodalMetrics_clicked(bool)));
     connect(this,SIGNAL(mySignalMgrayBoxCP_NodalMetrics(bool)),this,SLOT(on_checkCP_NodalMetrics_clicked(bool)));


     emit mySignalMclr();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSave_clicked()
{
    if (operating_system != os_win32 && operating_system != os_linux) {
        std::cout << "Not win32 or linux!" << std::endl;

    }

    std::stringstream script;
    script <<  "echo unweightednetworks" << std::endl;

    if (ui->checkCUCorMat->isChecked()) {
        //组合之外的统统选n
        if (ui->lineEditCUCorMat_Dir_for_BOLD->text().isEmpty()
                || ui->lineEditCUCorMat_threshold_for_mask->text().isEmpty()
                //|| ui->lineEditCUCorMat_to_average->text().isEmpty()
                //|| ui->lineEditCUCorMat_to_save_cormatrix->text().isEmpty()
                //|| ui->lineEditCUCorMat_threshold_type->text().isEmpty()
                || ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        if(individual_metrics==0&&average_ordinary==1&&average_fisher==0)
        script << (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe " : "./exefiles/CUCormat ") <<
              ui->lineEditCUCorMat_Dir_for_BOLD->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_mask->text().toStdString() <<
              ' ' <<
              "yn" <<
                  //ui->lineEditCUCorMat_to_average->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_to_save_cormatrix->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_to_save_cormatrix->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_threshold_type->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_threshold_type->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().toStdString() <<
              std::endl;
        else if(individual_metrics==1&&average_ordinary==1&&average_fisher==0)
        script << (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe " : "./exefiles/CUCormat ") <<
              ui->lineEditCUCorMat_Dir_for_BOLD->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_mask->text().toStdString() <<
              ' ' <<
              "bn" <<
                  //ui->lineEditCUCorMat_to_average->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_to_save_cormatrix->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_to_save_cormatrix->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_threshold_type->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_threshold_type->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().toStdString() <<
              std::endl;
        else if(individual_metrics==0&&average_ordinary==1&&average_fisher==1)
        script << (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe " : "./exefiles/CUCormat ") <<
              ui->lineEditCUCorMat_Dir_for_BOLD->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_mask->text().toStdString() <<
              ' ' <<
              "yf" <<
                  //ui->lineEditCUCorMat_to_average->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_to_save_cormatrix->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_to_save_cormatrix->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_threshold_type->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_threshold_type->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().toStdString() <<
              std::endl;
        else if(individual_metrics==1&&average_ordinary==1&&average_fisher==1)
        script << (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe " : "./exefiles/CUCormat ") <<
              ui->lineEditCUCorMat_Dir_for_BOLD->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_mask->text().toStdString() <<
              ' ' <<
              "bf" <<
                  //ui->lineEditCUCorMat_to_average->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_to_save_cormatrix->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_to_save_cormatrix->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_threshold_type->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_threshold_type->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().toStdString() <<
              std::endl;
        else //if(individual_metrics==1&&average_ordinary==1&&average_fisher==0)
        script << (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe " : "./exefiles/CUCormat ") <<
              ui->lineEditCUCorMat_Dir_for_BOLD->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_mask->text().toStdString() <<
              ' ' <<
              "n" <<
                  //ui->lineEditCUCorMat_to_average->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_to_save_cormatrix->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_to_save_cormatrix->text().toStdString() <<
              ' ' <<
              ui->comboBoxCUCorMat_threshold_type->currentText().toStdString() <<
                  //ui->lineEditCUCorMat_threshold_type->text().toStdString() <<
              ' ' <<
              ui->lineEditCUCorMat_threshold_for_correlation_coefficient->text().toStdString() <<
              std::endl;
    }

    if (ui->checkLp->isChecked()) {
        if (ui->lineEditLp_input_dir->text().isEmpty()
                || ui->lineEditLp_num_of_random_networks->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
         string sc=ui->comboBoxLp_type_for_Lp->currentText().toStdString();
         if(sc=="BFW_CUDA")
        script << (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp.exe " : "./exefiles/CUBFW_Lp ") <<
              ui->lineEditLp_input_dir->text().toStdString() <<
              ' ' <<
              ui->lineEditLp_num_of_random_networks->text().toStdString() <<
              std::endl;
         else if(sc=="BFS_MulCPU")
             script << (operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU.exe " : "./exefiles/BFS_MulCPU ") <<
                   ui->lineEditLp_input_dir->text().toStdString() <<
                   ' ' <<
                   ui->lineEditLp_num_of_random_networks->text().toStdString() <<
                   std::endl;
    }

 /*   if (ui->checkCUBFS_Lp->isChecked()) {
        if (ui->lineEditCUBFS_Lp_input_dir->text().isEmpty()
                || ui->lineEditCUBFS_Lp_num_of_random_networks->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\CUBFS_Lp.exe " : "./exefiles/CUBFS_Lp ") <<
              ui->lineEditCUBFS_Lp_input_dir->text().toStdString() <<
              ' ' <<
              ui->lineEditCUBFS_Lp_num_of_random_networks->text().toStdString() <<
              std::endl;
    }*/
/*
    if (ui->checkBFS_MulCPU->isChecked()) {
        if (ui->lineEditBFS_MulCPU_input_dir->text().isEmpty()
                || ui->lineEditBFS_MulCPU_num_of_random_networks->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU.exe " : "./exefiles/BFS_MulCPU ") <<
              ui->lineEditBFS_MulCPU_input_dir->text().toStdString() <<
              ' ' <<
              ui->lineEditBFS_MulCPU_num_of_random_networks->text().toStdString() <<
              std::endl;
    }
*/
    if (ui->checkCP->isChecked()) {
        if (ui->lineEditCp_input_dir->text().isEmpty()
                || ui->lineEditCp_num_of_random_networks->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\Cp.exe " : "./exefiles/Cp ") <<
              ui->lineEditCp_input_dir->text().toStdString() <<
              ' ' <<
              ui->lineEditCp_num_of_random_networks->text().toStdString() <<
              std::endl;
    }

    if (ui->checkDegree->isChecked()) {
        if (ui->lineEditDegree_input_dir->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\Degree.exe " : "./exefiles/Degree ") <<
              ui->lineEditDegree_input_dir->text().toStdString() <<
              std::endl;
    }

    if (ui->checkCUBC->isChecked()) {
        if (ui->lineEditCUBC_input_dir->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\CUBC.exe " : "./exefiles/CUBC ") <<
              ui->lineEditCUBC_input_dir->text().toStdString() <<
              std::endl;
    }

    if (ui->checkCUEC->isChecked()) {
        if (ui->lineEditCUEC_input_dir->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\CUEC.exe " : "./exefiles/CUBC ") <<
              ui->lineEditCUEC_input_dir->text().toStdString() <<
              std::endl;
    }



    if (ui->checkL_Modularity->isChecked()) {
        if (ui->lineEditL_Modularity_dir_for_csr->text().isEmpty()
                || ui->lineEditL_Modularity_num_of_random_networks->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }                                           //这句话是看是不是win32 是就是一种格式 不是就是另一种格式  \\是c++中的转义字符  代表win中的反斜杠；系统路径，编程路径 \\或/ 理解：因为\会被编译错

        string s=ui->comboBoxLouvain_Modularity_modularity_type->currentText().toStdString();
        if(s=="Louvain")
           script << (operating_system == os_win32 ? ".\\exefiles\\Louvain_Modularity.exe " : "./exefiles/Louvain_Modularity ") <<
                 ui->lineEditL_Modularity_dir_for_csr->text().toStdString() <<
                 ' ' <<
                 ui->lineEditL_Modularity_num_of_random_networks->text().toStdString() <<
                 std::endl;
        else if (s=="Newman_GPU")
            script << (operating_system == os_win32 ? ".\\exefiles\\Newman_Modularity_GPU.exe " : "./exefiles/Newman_Modularity_GPU ") <<
                        ui->lineEditL_Modularity_dir_for_csr->text().toStdString() <<
                        ' ' <<
                        ui->lineEditL_Modularity_num_of_random_networks->text().toStdString() <<
                        std::endl;
         else
            script << (operating_system == os_win32 ? ".\\exefiles\\Newman_Modularity_CPU.exe " : "./exefiles/Newman_Modularity_CPU ") <<
                         ui->lineEditL_Modularity_dir_for_csr->text().toStdString() <<
                         ' ' <<
                         ui->lineEditL_Modularity_num_of_random_networks->text().toStdString() <<
                         std::endl;

    }
    if (ui->checkPC_CPU->isChecked()) {
        if (ui->lineEditPC_CPU_input_dir->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        string s1=ui->comboBoxPC_CPU_type_for_participant_coefficient->currentText().toStdString();
        if(s1=="normalized")
        script << (operating_system == os_win32 ? ".\\exefiles\\PC_CPU.exe " : "./exefiles/PC_CPU ") <<
              ui->lineEditPC_CPU_input_dir->text().toStdString() <<
              ' ' <<
           //   ui->lineEditPC_CPU_type_for_participant_coefficient->text().toStdString() <<
              "n" <<
                  std::endl;
        else  script << (operating_system == os_win32 ? ".\\exefiles\\PC_CPU.exe " : "./exefiles/PC_CPU ") <<
                        ui->lineEditPC_CPU_input_dir->text().toStdString() <<
                        ' ' <<
                            std::endl;
    }
    if (ui->checkConvertNII->isChecked()) {
        if (ui->lineEditConvertNII_input_file->text().isEmpty()
                || ui->lineEditConvertNII_mask_file->text().isEmpty()
                || ui->lineEditConvertNII_mask_threshold->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\ConvertNII.exe " : "./exefiles/ConvertNII ") <<
              ui->lineEditConvertNII_input_file->text().toStdString() <<
              ' ' <<
              ui->lineEditConvertNII_mask_file->text().toStdString() <<
              ' ' <<
              ui->lineEditConvertNII_mask_threshold->text().toStdString() <<
              std::endl;
    }
    if (ui->checkLp_NodalMetrics->isChecked()) {

        if (ui->lineEditLp_input_dir_NodalMetrics->text().isEmpty()
                || ui->lineEditLp_num_of_random_networks_NodalMetrics->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
         string sc=ui->comboBoxLp_type_for_Lp_NodalMetrics->currentText().toStdString();
         if(sc=="BFW_CUDA")
        script << (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp.exe " : "./exefiles/CUBFW_Lp ") <<
              ui->lineEditLp_input_dir_NodalMetrics->text().toStdString() <<
              ' ' <<
              ui->lineEditLp_num_of_random_networks_NodalMetrics->text().toStdString() <<
              std::endl;
         else if(sc=="BFS_MulCPU")
             script << (operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU.exe " : "./exefiles/BFS_MulCPU ") <<
                   ui->lineEditLp_input_dir_NodalMetrics->text().toStdString() <<
                   ' ' <<
                   ui->lineEditLp_num_of_random_networks_NodalMetrics->text().toStdString() <<
                   std::endl;

    }
    if (ui->checkCP_NodalMetrics->isChecked()) {
        if (ui->lineEditCp_input_dir_NodalMetrics->text().isEmpty()
                || ui->lineEditCp_num_of_random_networks_NodalMetrics->text().isEmpty()) {
            QMessageBox::information(this, "Error", "Empty parameter(s).", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        script << (operating_system == os_win32 ? ".\\exefiles\\Cp.exe " : "./exefiles/Cp ") <<
              ui->lineEditCp_input_dir_NodalMetrics->text().toStdString() <<
              ' ' <<
              ui->lineEditCp_num_of_random_networks_NodalMetrics->text().toStdString() <<
              std::endl;
    }


    QString file_name = ui->lineEditSaveDir->text();
    std::cout << script.str() << std::endl;
    QFileInfo file_info(file_name);
    if (!file_info.exists()) {//是指文件不存在，只有text内容为空文件才会不存在
        file_name = QFileDialog::getSaveFileName(this,
                                                         "Save as..." ,
                                                         (operating_system == os_win32 ? "script.bat" : "script.sh"),
                                                         (operating_system == os_win32 ? "script (*.bat);;Any (*.*)" : "script (*.sh);Any (*.*)"));

    }

    //filename为空，赋值为null
    if (!file_name.isNull()) { //不空1.怎么知道os是哪种输出设备？2.
        ui->lineEditSaveDir->setText(file_name);
        std::ofstream os;
        os.open(file_name.toStdString().c_str());
        os << script.str();//.str表示一份拷贝
        os.close();   //保存完了

        if (operating_system == os_win32) {
            std::string cmd = "start " + file_name.toStdString() + " &";
            system(cmd.c_str());
        } else {
            std::string cmd = "sh " + file_name.toStdString() + " &";
            system(cmd.c_str());
        }    //执行命令
    }
    /*if (ui->lineEditSaveDir->text().isEmpty()) {
        on_toolButtonSaveDir_clicked();
    }
    QString file_name = ui->lineEditSaveDir->text();
    if (!file_name.isNull()) {
        file_name += ((operating_system == win32) ? "/script.bat" : "script.sh");
        std::ofstream os;
        os.open(file_name.toStdString().c_str());
        os << script.str();
        os.close();
    }*/

}

void MainWindow::on_pushButtonLoad_clicked()
{
     bool flag_cancel=false;
    //QString file_name = ui->lineEditSaveDir->text();
      QString file_name = QString::null;
    // file_name += ((operating_system == win32) ? "/script.bat" : "script.sh");
    QFileInfo file_info(file_name);
    if (!file_info.exists()) {
       if(file_name_transimit==NULL){
        file_name = QFileDialog::getOpenFileName(this,
                                                 "Save as..." ,
                                                 (operating_system == os_win32 ? "script.bat" : "script.sh"),//你的一系列选择脚本的操作相当于给变量赋值
                                                 (operating_system == os_win32 ? "script (*.bat);;Any (*.*)" : "script (*.sh);Any (*.*)"));
       if(file_name==NULL){
           flag_cancel=true;
       }
       }else {
           file_name=file_name_transimit;
           file_name_transimit=QString::null;
           qDebug("finish assignment");
       }
       ui->lineEditSaveDir->setText(file_name);
    }
    std::ifstream is;
    is.open(file_name.toStdString().c_str());
    std::string line;

    ui->checkCUCorMat->setChecked(false);
    ui->checkLp->setChecked(false);
    //ui->checkCUBFS_Lp->setChecked(false);
    //ui->checkBFS_MulCPU->setChecked(false);
    ui->checkCP->setChecked(false);
    ui->checkDegree->setChecked(false);
    ui->checkCUBC->setChecked(false);
    ui->checkCUEC->setChecked(false);
    ui->checkConvertNII->setChecked(false);
    ui->checkL_Modularity->setChecked(false);
    ui->checkPC_CPU->setChecked(false);
    ui->checkLp_NodalMetrics->setChecked(false);
    ui->checkCP_NodalMetrics->setChecked(false);

    int flag=0;
    while (std::getline(is, line)) {  //这个的意思是读完整个文件，我去，太牛了！
        //ui->lineEditSaveDir->setText(line.c_str());
        std::vector<std::string> tokens; //在命名空间中再找一个特定的命名空间
        std::string token;
        std::istringstream line_is(line);//在循环中定义的变量在每次循环里都要经历创建和撤消的过程
        while (line_is >> token) {
            tokens.push_back(token); //把line_is的数据输到向量tokens，若输入一直有，为真，就一直输入
        }

        //std::string out;
        //for (size_t i = 0; i < tokens.size(); ++i) {
        //    out += tokens[i] + " ";
        //}
        //ui->lineEditSaveDir->setText(out.c_str());

        if (tokens.empty())
            continue;       //一行一行的输入！

        if(tokens[0] =="echo"){  //原则 1.2.若没有调用该if语句，即判断为warning

            if(tokens[1] =="unweightednetworks"){
                flag++;
                //不切换界面，处理参数
                continue;
            }else if((tokens[1] =="weightednetworks")){
                flag++;
                //切换界面，传递参数,发射信号
                this->hide();// 1.切换界面
                w1.setParent(this);
                w1.show();
                //2.传递参数 用全局变量extern哈哈哈！
                file_name_transimit=file_name;
                //发射信号
                emit  mySignalMtoS();
            }
        }
        if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUCorMat.exe" : "./exefiles/CUCormat")) {
            if (tokens.size() >= 7) {
                ui->checkCUCorMat->setChecked(true);
                 emit mySignalMgrayBoxCUCorMat(true);
                ui->lineEditCUCorMat_Dir_for_BOLD->setText(tokens[1].c_str());
                ui->lineEditCUCorMat_threshold_for_mask->setText(tokens[2].c_str());
                if(tokens[3] == "n")
                {
                ui->radioButton_CUCorMat_to_average->setChecked(true);
                ui->ordinary->setChecked(false);
                ui->fisher->setChecked(false);
                }else if(tokens[3] == "yf")
                {
                ui->radioButton_CUCorMat_to_average->setChecked(false);
                ui->ordinary->setChecked(true);
                ui->fisher->setChecked(true);
                }else if(tokens[3] == "yn")
                {
                ui->radioButton_CUCorMat_to_average->setChecked(false);
                ui->ordinary->setChecked(true);
                ui->fisher->setChecked(false);
                }else if(tokens[3] == "bn")
                {
                ui->radioButton_CUCorMat_to_average->setChecked(true);
                ui->ordinary->setChecked(true);
                ui->fisher->setChecked(false);
                }else if(tokens[3] == "bf")
                {
                ui->radioButton_CUCorMat_to_average->setChecked(true);
                ui->ordinary->setChecked(true);
                ui->fisher->setChecked(true);
                }
                ui->comboBoxCUCorMat_to_save_cormatrix->setCurrentIndex(tokens[4] == "y");
                ui->comboBoxCUCorMat_threshold_type->setCurrentIndex(tokens[5] == "s");
                //ui->lineEditCUCorMat_to_average->setText(tokens[3].c_str());
                //ui->lineEditCUCorMat_to_save_cormatrix->setText(tokens[4].c_str());
                //ui->lineEditCUCorMat_threshold_type->setText(tokens[5].c_str());
                std::string token6;
                for (size_t i = 6; i < tokens.size(); ++i)
                    token6 += tokens[i] + " ";
                ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setText(token6.c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp.exe" : "./exefiles/CUBFW_Lp")||tokens[0] ==(operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU.exe" : "./exefiles/BFS_MulCPU")) {
            if (tokens.size() == 3) {
                ui->checkLp->setChecked(true);
                emit mySignalMgrayBoxLp(true);
                if(tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp.exe" : "./exefiles/CUBFW_Lp"))
                  ui->comboBoxLp_type_for_Lp->setCurrentIndex(0);
                else if(tokens[0] ==(operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU.exe" : "./exefiles/BFS_MulCPU"))
                    ui->comboBoxLp_type_for_Lp->setCurrentIndex(1);
                ui->lineEditLp_input_dir->setText(tokens[1].c_str());
                ui->lineEditLp_num_of_random_networks->setText(tokens[2].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Cp.exe" : "./Cp")) {
            if (tokens.size() == 3) {
                ui->checkCP->setChecked(true);
                emit mySignalMgrayBoxCP(true);
                ui->lineEditCp_input_dir->setText(tokens[1].c_str());
                ui->lineEditCp_num_of_random_networks->setText(tokens[2].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Degree.exe" : "./exefiles/Degree")) {
            if (tokens.size() == 2) {
                ui->checkDegree->setChecked(true);
                emit mySignalMgrayBoxDegree(true);
                ui->lineEditDegree_input_dir->setText(tokens[1].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUBC.exe" : "./exefiles/CUBC")) {
            if (tokens.size() == 2) {
                ui->checkCUBC->setChecked(true);
                emit mySignalMgrayBoxCUBC(true);
                ui->lineEditCUBC_input_dir->setText(tokens[1].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUEC.exe" : "./exefiles/CUEC")) {
            if (tokens.size() == 2) {
                ui->checkCUEC->setChecked(true);
                emit mySignalMgrayBoxCUEC(true);
                ui->lineEditCUEC_input_dir->setText(tokens[1].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\ConvertNII.exe" : "./exefiles/ConvertNII")) {
            if (tokens.size() == 4) {
                ui->checkConvertNII->setChecked(true);
                emit mySignalMgrayBoxConvertNII(true);
                ui->lineEditConvertNII_input_file->setText(tokens[1].c_str());
                ui->lineEditConvertNII_mask_file->setText(tokens[2].c_str());
                ui->lineEditConvertNII_mask_threshold->setText(tokens[3].c_str());
            }
        } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Louvain_Modularity.exe" : "./exefiles/Louvain_Modularity")
                  ||tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Newman_Modularity_GPU.exe" : "./exefiles/Newman_Modularity_GPU")
                  || tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Newman_Modularity_CPU.exe" : "./exefiles/Newman_Modularity_CPU")
                   ) {
            if (tokens.size() == 3) {
                ui->checkL_Modularity->setChecked(true);
                emit mySignalMgrayBoxL_Modularity(true);
                if(tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Louvain_Modularity.exe" : "./exefiles/Louvain_Modularity"))
                ui->comboBoxLouvain_Modularity_modularity_type->setCurrentIndex(0);
                else if(tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Newman_Modularity_GPU.exe" : "./exefiles/Newman_Modularity_GPU") )
                ui->comboBoxLouvain_Modularity_modularity_type->setCurrentIndex(1);
                else ui->comboBoxLouvain_Modularity_modularity_type->setCurrentIndex(2);
                ui->lineEditL_Modularity_dir_for_csr->setText(tokens[1].c_str());
                ui->lineEditL_Modularity_num_of_random_networks->setText(tokens[2].c_str());
            }
        }else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\PC_CPU.exe" : "./exefiles/PC_CPU")) {
            if (tokens.size() == 3) {
                ui->checkPC_CPU->setChecked(true);
                emit mySignalMgrayBoxPC_CPU(true);
                ui->lineEditPC_CPU_input_dir->setText(tokens[1].c_str());
                ui->comboBoxPC_CPU_type_for_participant_coefficient->setCurrentIndex(tokens[2] == "n");
            }
             else if (tokens.size() == 2) {
                ui->checkPC_CPU->setChecked(true);
                emit mySignalMgrayBoxPC_CPU(true);
                ui->lineEditPC_CPU_input_dir->setText(tokens[1].c_str());
                ui->comboBoxPC_CPU_type_for_participant_coefficient->setCurrentIndex(0);
            }
        }

        // ui->lineEditSaveDir->setText(QString(token.c_str()));
        //这里要改！！！
    else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp_NodalMetrics.exe" : "./exefiles/CUBFW_Lp_NodalMetrics")||tokens[0] ==(operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU_NodalMetrics.exe" : "./exefiles/BFS_MulCPU_NodalMetrics")) {
        if (tokens.size() == 3) {
            ui->checkLp_NodalMetrics->setChecked(true);
            emit mySignalMgrayBoxLp_NodalMetrics(true);
            if(tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\CUBFW_Lp_NodalMetrics.exe" : "./exefiles/CUBFW_Lp_NodalMetrics"))
              ui->comboBoxLp_type_for_Lp_NodalMetrics->setCurrentIndex(0);
            else if(tokens[0] ==(operating_system == os_win32 ? ".\\exefiles\\BFS_MulCPU_NodalMetrics.exe" : "./exefiles/BFS_MulCPU_NodalMetrics"))
                ui->comboBoxLp_type_for_Lp_NodalMetrics->setCurrentIndex(1);
            ui->lineEditLp_input_dir_NodalMetrics->setText(tokens[1].c_str());
            ui->lineEditLp_num_of_random_networks_NodalMetrics->setText(tokens[2].c_str());
        }
    } else if (tokens[0] == (operating_system == os_win32 ? ".\\exefiles\\Cp_NodalMetrics.exe" : "./Cp_NodalMetrics")) {
        if (tokens.size() == 3) {
            ui->checkCP_NodalMetrics->setChecked(true);
            emit mySignalMgrayBoxCP_NodalMetrics(true);
            ui->lineEditCp_input_dir_NodalMetrics->setText(tokens[1].c_str());
            ui->lineEditCp_num_of_random_networks_NodalMetrics->setText(tokens[2].c_str());
        }
    }
    if(flag==0&&flag_cancel==false){  //这儿有debug！！！
         QMessageBox::information(this, "Warning", "Empty parameter(s).Error(s) may occur.Please advise on the network type (weighted or unweighted) by using the command:echo", QMessageBox::Ok, QMessageBox::Ok);
         //清理参数，必须这样，要不乱了·· 这个不要求echo语句的位置！好优点！``所以必须在这统一清理参数！
         emit mySignalMclr();
    };

    is.close();

}
}
void MainWindow::on_toolButtonCUCorMat_Dir_for_BOLD_clicked()
{
    ui->lineEditCUCorMat_Dir_for_BOLD->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_toolButtonLp_input_dir_clicked()
{
    ui->lineEditLp_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

/*void MainWindow::on_toolButtonCUBFS_Lp_input_dir_clicked()
{
    ui->lineEditCUBFS_Lp_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}*/
/*
void MainWindow::on_toolButtonBFS_MulCPU_input_dir_clicked()
{
    ui->lineEditBFS_MulCPU_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}*/

void MainWindow::on_toolButtonCp_input_dir_clicked()
{
    ui->lineEditCp_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_toolButtonDegree_input_dir_clicked()
{
    ui->lineEditDegree_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_toolButtonCUBC_input_dir_clicked()
{
    ui->lineEditCUBC_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_toolButtonCUEC_input_dir_clicked()
{
     ui->lineEditCUEC_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}


void MainWindow::on_toolButtonConvertNII_input_file_clicked()
{
  /*  ui->lineEditConvertNII_input_file->setText(QFileDialog::getOpenFileName(this,
                                                                            "File to convert",
                                                                            "",
                                                                            "CP (*.cp); EFF (*.eff); DEG (*.deg); BC (*.bc); Any (*.*)"));
  */
    ui->lineEditConvertNII_input_file->setText(QFileDialog::getExistingDirectory(this,
                                                                            "Directory"
                                                                            ));
}

void MainWindow::on_toolButtonConvertNII_mask_file_clicked()
{
    ui->lineEditConvertNII_mask_file->setText(QFileDialog::getOpenFileName(this,
                                                                          "NII File",
                                                                          "",
                                                                          "NII (*.nii)"));

  /*  ui->lineEditConvertNII_mask_file->setText(QFileDialog::getExistingDirectory(this,
                                                                              "Directory"

                                                                              ));*/
}
void MainWindow::on_toolButtonL_Modularity_dir_for_csr_clicked()
{
    ui->lineEditL_Modularity_dir_for_csr->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_toolButtonSaveDir_clicked()
{
    ui->lineEditSaveDir->setText(QFileDialog::getOpenFileName(this,
                                                              "Open script..." ,
                                                              (operating_system == os_win32 ? "*.bat" : "*.sh"),
                                                              (operating_system == os_win32 ? "script (*.bat);;Any (*.*)" : "script (*.sh);Any (*.*)")));
}

void MainWindow::on_switchButton_clicked()
{
    this->hide();
    //weightednetwork w;
   // w1=new weightednetwork();
   w1.setParent(this);
    w1.show();
}

void MainWindow::on_toolButtonPC_CPU_clicked()
{
    ui->lineEditPC_CPU_input_dir->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_checkCUCorMat_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCUCorMat_Dir_for_BOLD->setEnabled(false);
         ui->lineEditCUCorMat_threshold_for_mask->setEnabled(false);
         ui->radioButton_CUCorMat_to_average->setEnabled(false);
         ui->ordinary->setEnabled(false);
         ui->fisher->setEnabled(false);
         ui->comboBoxCUCorMat_to_save_cormatrix->setEnabled(false);
         ui->comboBoxCUCorMat_threshold_type->setEnabled(false);
         ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setEnabled(false);
         ui->toolButtonCUCorMat_Dir_for_BOLD->setEnabled(false);

         ui->labelCUCorMat_Dir_for_BOLD->setVisible(false);
         ui->lineEditCUCorMat_Dir_for_BOLD->setVisible(false);
         ui->toolButtonCUCorMat_Dir_for_BOLD->setVisible(false);

         ui->labelCUCorMat_threshold_for_mask->setVisible(false);
         ui->lineEditCUCorMat_threshold_for_mask->setVisible(false);

         ui->labelCUCorMat_to_average->setVisible(false);
         ui->groupBoxCUCorMat_to_average->setVisible(false);

         ui->labelCUCorMat_to_save_cormatrix->setVisible(false);
         ui->comboBoxCUCorMat_to_save_cormatrix->setVisible(false);

         ui->labelCUCorMat_threshold_type->setVisible(false);
         ui->comboBoxCUCorMat_threshold_type->setVisible(false);

         ui->labelCUCorMat_threshold_for_correlation_coefficient->setVisible(false);
         ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setVisible(false);
    }
     else if(checked==1)
     {
        ui->lineEditCUCorMat_Dir_for_BOLD->setEnabled(true);
        ui->lineEditCUCorMat_threshold_for_mask->setEnabled(true);
        ui->radioButton_CUCorMat_to_average->setEnabled(true);
        ui->ordinary->setEnabled(true);
        ui->fisher->setEnabled(true);
        ui->comboBoxCUCorMat_to_save_cormatrix->setEnabled(true);
        ui->comboBoxCUCorMat_threshold_type->setEnabled(true);
        ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setEnabled(true);
        ui->toolButtonCUCorMat_Dir_for_BOLD->setEnabled(true);


        ui->labelCUCorMat_Dir_for_BOLD->setVisible(true);
        ui->lineEditCUCorMat_Dir_for_BOLD->setVisible(true);
        ui->toolButtonCUCorMat_Dir_for_BOLD->setVisible(true);

        ui->labelCUCorMat_threshold_for_mask->setVisible(true);
        ui->lineEditCUCorMat_threshold_for_mask->setVisible(true);

        ui->labelCUCorMat_to_average->setVisible(true);
        ui->groupBoxCUCorMat_to_average->setVisible(true);

        ui->labelCUCorMat_to_save_cormatrix->setVisible(true);
        ui->comboBoxCUCorMat_to_save_cormatrix->setVisible(true);

        ui->labelCUCorMat_threshold_type->setVisible(true);
        ui->comboBoxCUCorMat_threshold_type->setVisible(true);

        ui->labelCUCorMat_threshold_for_correlation_coefficient->setVisible(true);
        ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setVisible(true);
    }
}

void MainWindow::on_toolButtonLp_input_dir_NodalMetrics_clicked()
{
    ui->lineEditLp_input_dir_NodalMetrics->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}
void MainWindow::on_toolButtonCp_input_dir_NodalMetrics_clicked()
{
     ui->lineEditCp_input_dir_NodalMetrics->setText(QFileDialog::getExistingDirectory(this, "Directory"));
}

void MainWindow::on_checkLp_clicked(bool checked)
{
    if(checked==0){
        ui->comboBoxLp_type_for_Lp->setEnabled(false);
         ui->lineEditLp_input_dir->setEnabled(false);
         ui->lineEditLp_num_of_random_networks->setEnabled(false);
         ui->toolButtonLp_input_dir->setEnabled(false);

         ui->labelLp_type_for_Lp->setVisible(false);
         ui->comboBoxLp_type_for_Lp->setVisible(false);
         ui->labelLp_input_dir->setVisible(false);
         ui->lineEditLp_input_dir->setVisible(false);
         ui->toolButtonLp_input_dir->setVisible(false);
         ui->labelLp_num_of_random_networks->setVisible(false);
         ui->lineEditLp_num_of_random_networks->setVisible(false);
    }
     else if(checked==1)
     {
        ui->comboBoxLp_type_for_Lp->setEnabled(true);
        ui->lineEditLp_input_dir->setEnabled(true);
        ui->lineEditLp_num_of_random_networks->setEnabled(true);
        ui->toolButtonLp_input_dir->setEnabled(true);

        ui->labelLp_type_for_Lp->setVisible(true);
        ui->comboBoxLp_type_for_Lp->setVisible(true);
        ui->labelLp_input_dir->setVisible(true);
        ui->lineEditLp_input_dir->setVisible(true);
        ui->toolButtonLp_input_dir->setVisible(true);
        ui->labelLp_num_of_random_networks->setVisible(true);
        ui->lineEditLp_num_of_random_networks->setVisible(true);
    }
}

/*void MainWindow::on_checkCUBFS_Lp_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCUBFS_Lp_input_dir->setEnabled(false);
         ui->lineEditCUBFS_Lp_num_of_random_networks->setEnabled(false);
         ui->toolButtonCUBFS_Lp_input_dir->setEnabled(false);
    }
     else if(checked==1)
     {
        ui->lineEditCUBFS_Lp_input_dir->setEnabled(true);
        ui->lineEditCUBFS_Lp_num_of_random_networks->setEnabled(true);
        ui->toolButtonCUBFS_Lp_input_dir->setEnabled(true);
    }
}*/
/*
void MainWindow::on_checkBFS_MulCPU_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditBFS_MulCPU_input_dir->setEnabled(false);
         ui->lineEditBFS_MulCPU_num_of_random_networks->setEnabled(false);
         ui->toolButtonBFS_MulCPU_input_dir->setEnabled(false);
    }
     else if(checked==1)
     {
        ui->lineEditBFS_MulCPU_input_dir->setEnabled(true);
        ui->lineEditBFS_MulCPU_num_of_random_networks->setEnabled(true);
        ui->toolButtonBFS_MulCPU_input_dir->setEnabled(true);
    }
}
*/
void MainWindow::on_checkCP_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCp_input_dir->setEnabled(false);
         ui->lineEditCp_num_of_random_networks->setEnabled(false);
         ui->toolButtonCp_input_dir->setEnabled(false);

         ui->labelCp_input_dir->setVisible(false);
         ui->lineEditCp_input_dir->setVisible(false);
         ui->toolButtonCp_input_dir->setVisible(false);
         ui->labelCp_num_of_random_networks->setVisible(false);
         ui->lineEditCp_num_of_random_networks->setVisible(false);
    }
     else if(checked==1)
     {
        ui->lineEditCp_input_dir->setEnabled(true);
        ui->lineEditCp_num_of_random_networks->setEnabled(true);
        ui->toolButtonCp_input_dir->setEnabled(true);

        ui->labelCp_input_dir->setVisible(true);
        ui->lineEditCp_input_dir->setVisible(true);
        ui->toolButtonCp_input_dir->setVisible(true);
        ui->labelCp_num_of_random_networks->setVisible(true);
        ui->lineEditCp_num_of_random_networks->setVisible(true);
    }
}

void MainWindow::on_checkDegree_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditDegree_input_dir->setEnabled(false);
         ui->toolButtonDegree_input_dir->setEnabled(false);



    }
     else if(checked==1)
     {
        ui->lineEditDegree_input_dir->setEnabled(true);
        ui->toolButtonDegree_input_dir->setEnabled(true);




    }
}

void MainWindow::on_checkCUBC_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCUBC_input_dir->setEnabled(false);
         ui->toolButtonCUBC_input_dir->setEnabled(false);
    }
     else if(checked==1)
     {
        ui->lineEditCUBC_input_dir->setEnabled(true);
        ui->toolButtonCUBC_input_dir->setEnabled(true);
    }
}

void MainWindow::on_checkCUEC_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCUEC_input_dir->setEnabled(false);
         ui->toolButtonCUEC_input_dir->setEnabled(false);
    }
     else if(checked==1)
     {
        ui->lineEditCUEC_input_dir->setEnabled(true);
        ui->toolButtonCUEC_input_dir->setEnabled(true);
    }
}

void MainWindow::on_checkL_Modularity_clicked(bool checked)
{
    if(checked==0){
         ui->comboBoxLouvain_Modularity_modularity_type->setEnabled(false);
         ui->lineEditL_Modularity_dir_for_csr->setEnabled(false);
         ui->lineEditL_Modularity_num_of_random_networks->setEnabled(false);
         ui->toolButtonL_Modularity_dir_for_csr->setEnabled(false);

         ui->labelL_Modularity_modularity_type->setVisible(false);
         ui->comboBoxLouvain_Modularity_modularity_type->setVisible(false);
         ui->labelL_Modularity_dir_for_csr->setVisible(false);
         ui->lineEditL_Modularity_dir_for_csr->setVisible(false);
         ui->toolButtonL_Modularity_dir_for_csr->setVisible(false);
         ui->labelL_Modularity_num_of_random_networks->setVisible(false);
         ui->lineEditL_Modularity_num_of_random_networks->setVisible(false);
    }
     else if(checked==1)
     {
        ui->comboBoxLouvain_Modularity_modularity_type->setEnabled(true);
        ui->lineEditL_Modularity_dir_for_csr->setEnabled(true);
        ui->lineEditL_Modularity_num_of_random_networks->setEnabled(true);
        ui->toolButtonL_Modularity_dir_for_csr->setEnabled(true);

        ui->labelL_Modularity_modularity_type->setVisible(true);
        ui->comboBoxLouvain_Modularity_modularity_type->setVisible(true);
        ui->labelL_Modularity_dir_for_csr->setVisible(true);
        ui->lineEditL_Modularity_dir_for_csr->setVisible(true);
        ui->toolButtonL_Modularity_dir_for_csr->setVisible(true);
        ui->labelL_Modularity_num_of_random_networks->setVisible(true);
        ui->lineEditL_Modularity_num_of_random_networks->setVisible(true);
    }

}

void MainWindow::on_checkPC_CPU_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditPC_CPU_input_dir->setEnabled(false);
         ui->toolButtonPC_CPU->setEnabled(false);
          ui->comboBoxPC_CPU_type_for_participant_coefficient->setEnabled(false);

          ui->labelPC_CPU_input_dir->setVisible(false);
          ui->lineEditPC_CPU_input_dir->setVisible(false);
          ui->toolButtonPC_CPU->setVisible(false);
          ui->labelPC_CPU_type_for_participant_coefficient->setVisible(false);
          ui->comboBoxPC_CPU_type_for_participant_coefficient->setVisible(false);
    }
     else if(checked==1)
     {
        ui->lineEditPC_CPU_input_dir->setEnabled(true);
        ui->toolButtonPC_CPU->setEnabled(true);
         ui->comboBoxPC_CPU_type_for_participant_coefficient->setEnabled(true);

         ui->labelPC_CPU_input_dir->setVisible(true);
         ui->lineEditPC_CPU_input_dir->setVisible(true);
         ui->toolButtonPC_CPU->setVisible(true);
         ui->labelPC_CPU_type_for_participant_coefficient->setVisible(true);
         ui->comboBoxPC_CPU_type_for_participant_coefficient->setVisible(true);
    }
}

void MainWindow::on_checkConvertNII_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditConvertNII_input_file->setEnabled(false);
         ui->lineEditConvertNII_mask_file->setEnabled(false);
         ui->lineEditConvertNII_mask_threshold->setEnabled(false);
         ui->toolButtonConvertNII_input_file->setEnabled(false);
         ui->toolButtonConvertNII_mask_file->setEnabled(false);

         ui->labelConvertNII_input_file->setVisible(false);
         ui->lineEditConvertNII_input_file->setVisible(false);
         ui->toolButtonConvertNII_input_file->setVisible(false);
         ui->labelConvertNII_mask_file->setVisible(false);
         ui->lineEditConvertNII_mask_file->setVisible(false);
         ui->toolButtonConvertNII_mask_file->setVisible(false);
         ui->labelConvertNII_mask_threshold->setVisible(false);
         ui->lineEditConvertNII_mask_threshold->setVisible(false);
    }
     else if(checked==1)
     {
        ui->lineEditConvertNII_input_file->setEnabled(true);
        ui->lineEditConvertNII_mask_file->setEnabled(true);
        ui->lineEditConvertNII_mask_threshold->setEnabled(true);
        ui->toolButtonConvertNII_input_file->setEnabled(true);
        ui->toolButtonConvertNII_mask_file->setEnabled(true);

        ui->labelConvertNII_input_file->setVisible(true);
        ui->lineEditConvertNII_input_file->setVisible(true);
        ui->toolButtonConvertNII_input_file->setVisible(true);
        ui->labelConvertNII_mask_file->setVisible(true);
        ui->lineEditConvertNII_mask_file->setVisible(true);
        ui->toolButtonConvertNII_mask_file->setVisible(true);
        ui->labelConvertNII_mask_threshold->setVisible(true);
        ui->lineEditConvertNII_mask_threshold->setVisible(true);
}
}
void MainWindow::on_checkLp_NodalMetrics_clicked(bool checked)
{
    if(checked==0){
        ui->comboBoxLp_type_for_Lp_NodalMetrics->setEnabled(false);
         ui->lineEditLp_input_dir_NodalMetrics->setEnabled(false);
         ui->lineEditLp_num_of_random_networks_NodalMetrics->setEnabled(false);
         ui->toolButtonLp_input_dir_NodalMetrics->setEnabled(false);

         ui->labelLp_type_for_Lp_NodalMetrics->setVisible(false);
         ui->comboBoxLp_type_for_Lp_NodalMetrics->setVisible(false);
         ui->labelLp_input_dir_NodalMetrics->setVisible(false);
         ui->lineEditLp_input_dir_NodalMetrics->setVisible(false);
         ui->toolButtonLp_input_dir_NodalMetrics->setVisible(false);
         ui->labelLp_num_of_random_networks_NodalMetrics->setVisible(false);
         ui->lineEditLp_num_of_random_networks_NodalMetrics->setVisible(false);
    }
     else if(checked==1)
     {
        ui->comboBoxLp_type_for_Lp_NodalMetrics->setEnabled(true);
        ui->lineEditLp_input_dir_NodalMetrics->setEnabled(true);
        ui->lineEditLp_num_of_random_networks_NodalMetrics->setEnabled(true);
        ui->toolButtonLp_input_dir_NodalMetrics->setEnabled(true);

        ui->labelLp_type_for_Lp_NodalMetrics->setVisible(true);
        ui->comboBoxLp_type_for_Lp_NodalMetrics->setVisible(true);
        ui->labelLp_input_dir_NodalMetrics->setVisible(true);
        ui->lineEditLp_input_dir_NodalMetrics->setVisible(true);
        ui->toolButtonLp_input_dir_NodalMetrics->setVisible(true);
        ui->labelLp_num_of_random_networks_NodalMetrics->setVisible(true);
        ui->lineEditLp_num_of_random_networks_NodalMetrics->setVisible(true);
    }
}
void MainWindow::on_checkCP_NodalMetrics_clicked(bool checked)
{
    if(checked==0){
         ui->lineEditCp_input_dir_NodalMetrics->setEnabled(false);
         ui->lineEditCp_num_of_random_networks_NodalMetrics->setEnabled(false);
         ui->toolButtonCp_input_dir_NodalMetrics->setEnabled(false);

         ui->labelCp_input_dir_NodalMetrics->setVisible(false);
         ui->lineEditCp_input_dir_NodalMetrics->setVisible(false);
         ui->toolButtonCp_input_dir_NodalMetrics->setVisible(false);
         ui->labelCp_num_of_random_networks_NodalMetrics->setVisible(false);
         ui->lineEditCp_num_of_random_networks_NodalMetrics->setVisible(false);
    }
     else if(checked==1)
     {
        ui->lineEditCp_input_dir_NodalMetrics->setEnabled(true);
        ui->lineEditCp_num_of_random_networks_NodalMetrics->setEnabled(true);
        ui->toolButtonCp_input_dir_NodalMetrics->setEnabled(true);

        ui->labelCp_input_dir_NodalMetrics->setVisible(true);
        ui->lineEditCp_input_dir_NodalMetrics->setVisible(true);
        ui->toolButtonCp_input_dir_NodalMetrics->setVisible(true);
        ui->labelCp_num_of_random_networks_NodalMetrics->setVisible(true);
        ui->lineEditCp_num_of_random_networks_NodalMetrics->setVisible(true);
    }
}

void MainWindow::clearscreen(){
    //清屏函数两个功能：1.清空内容,顺带初始化；2.使界面回到灰框状态
    //1.清空内容；
    ui->lineEditCUCorMat_Dir_for_BOLD->setText("");
    ui->lineEditCUCorMat_threshold_for_mask->setText("");
    ui->radioButton_CUCorMat_to_average->setChecked(false);
    ui->ordinary->setChecked(false);
    ui->fisher->setChecked(false);

    ui->comboBoxCUCorMat_to_save_cormatrix->setCurrentIndex(0);
    ui->comboBoxCUCorMat_threshold_type->setCurrentIndex(0);
    ui->lineEditCUCorMat_threshold_for_correlation_coefficient->setText("");

    ui->lineEditLp_input_dir->setText("");;
    ui->lineEditLp_num_of_random_networks->setText("");
    ui->toolButtonLp_input_dir->setEnabled(false);

    //ui->lineEditCUBFS_Lp_input_dir->setText("");
    //ui->lineEditCUBFS_Lp_num_of_random_networks->setText("");
/*
    ui->lineEditBFS_MulCPU_input_dir->setText("");
    ui->lineEditBFS_MulCPU_num_of_random_networks->setText("");
*/
    ui->lineEditCp_input_dir->setText("");
    ui->lineEditCp_num_of_random_networks->setText("");

      ui->lineEditDegree_input_dir->setText("");

      ui->lineEditCUBC_input_dir->setText("");

       ui->lineEditCUEC_input_dir->setText("");

       ui->comboBoxLouvain_Modularity_modularity_type->setCurrentIndex(0);
       ui->lineEditL_Modularity_dir_for_csr->setText("");
       ui->lineEditL_Modularity_num_of_random_networks->setText("");

       ui->lineEditPC_CPU_input_dir->setText("");
       ui->comboBoxPC_CPU_type_for_participant_coefficient->setCurrentIndex(0);

       ui->lineEditConvertNII_input_file->setText("");
       ui->lineEditConvertNII_mask_file->setText("");
       ui->lineEditConvertNII_mask_threshold->setText("");


       ui->lineEditLp_input_dir_NodalMetrics->setText("");;
       ui->lineEditLp_num_of_random_networks_NodalMetrics->setText("");
       ui->toolButtonLp_input_dir_NodalMetrics->setEnabled(false);

       //ui->lineEditCUBFS_Lp_input_dir->setText("");
       //ui->lineEditCUBFS_Lp_num_of_random_networks->setText("");
   /*
       ui->lineEditBFS_MulCPU_input_dir->setText("");
       ui->lineEditBFS_MulCPU_num_of_random_networks->setText("");
   */
       ui->lineEditCp_input_dir_NodalMetrics->setText("");
       ui->lineEditCp_num_of_random_networks_NodalMetrics->setText("");
       //2.使界面回到灰框状态 good method
       emit mySignalMgrayBoxCUCorMat(false);
       emit mySignalMgrayBoxLp(false);
       //emit mySignalMgrayBoxCUBFS_Lp(false);
     //  emit mySignalMgrayBoxBFS_MulCPU(false);
       emit mySignalMgrayBoxCP(false);
       emit mySignalMgrayBoxDegree(false);
       emit mySignalMgrayBoxCUBC(false);
       emit mySignalMgrayBoxCUEC(false);
       emit mySignalMgrayBoxL_Modularity(false);
       emit mySignalMgrayBoxPC_CPU(false);
       emit mySignalMgrayBoxConvertNII(false);
       emit mySignalMgrayBoxLp_NodalMetrics(false);
       emit mySignalMgrayBoxCP_NodalMetrics(false);

}
//这是个鸡肋！适时删了它
/*
int label2flag=0;
void MainWindow::on_a_clicked(bool checked)
{
    label2flag++;
    if(label2flag>1)
        label2flag=0;
     if(label2flag==1){
         ui->widget->setMaximumHeight(24);
         ui->label_2->setText("Calculate the characteristic path length of the network.");
         ui->label_2->setGeometry(0,-23,641,71);
         ui->a->setGeometry(570,3,21,21);
         ui->a->setText("");
     }
     else
     {
         ui->widget->setMaximumHeight(69);
         ui->label_2->setText("Calculate the characteristic path length of the network and compare with K (user specified) random networks. Based on blocked Floyd-Warshall algorithm (BFW).");
         ui->label_2->setGeometry(0,-6,641,71);
         ui->a->setGeometry(390,41,21,21);
         ui->a->setText("");

     }
}
*/
void MainWindow::on_toolButton_Working_Directory_clicked()
{
   QString directory=QFileDialog::getExistingDirectory(this, "Directory");
    ui->lineEdit_Working_Directory->setText(directory);
    ui->lineEditLp_input_dir->setText(directory);
    //ui->lineEditBFS_MulCPU_input_dir->setText(directory);
    ui->lineEditCp_input_dir->setText(directory);
    ui->lineEditDegree_input_dir->setText(directory);
    ui->lineEditCUBC_input_dir->setText(directory);
    ui->lineEditCUEC_input_dir->setText(directory);
    ui->lineEditPC_CPU_input_dir->setText(directory);
    ui->lineEditConvertNII_input_file->setText(directory);
}

void MainWindow::on_toolButton_Mask_File_clicked()
{
  QString file = QFileDialog::getOpenFileName(this,"NII File","","NII (*.nii)");
    ui->lineEdit_Mask_File->setText(file);
    ui->lineEditConvertNII_mask_file->setText(file);
}






void MainWindow::on_radioButton_CUCorMat_to_average_clicked(bool checked)
{
    if(checked==0)
        individual_metrics=0;
    else if(checked==1)
        individual_metrics=1;
}

void MainWindow::on_ordinary_clicked(bool checked)
{
    if(checked==0)
        average_ordinary=0;
    else if(checked==1)
        average_ordinary=1;
}

void MainWindow::on_fisher_clicked(bool checked)
{
    if(checked==0)
        average_fisher=0;
    else if(checked==1)
        average_fisher=1;

}