# -*- coding: utf-8 -*-
'''
Created on 2013-4-24

@author: vincent
'''

import win32com.client
import types
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4 import QtCore, QtGui, QAxContainer
import sys
import copy

QTextCodec.setCodecForTr(QTextCodec.codecForName("utf8"))

class MainDialog(QDialog):
    def __init__(self, parent = None):
        super(MainDialog, self).__init__(parent)
        
        self.setWindowTitle("Process Access SQL")
        self.resize(520, 350)
        self.setSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.MinimumExpanding)
        self.data_Group = QGroupBox(self)
        self.data_Group.setTitle(self.tr("数据库"))
        self.data_Group.resize(400, 300)
        self.list_View = QListWidget(self.data_Group)
        self.list_View.setGeometry(15, 15, 390, 300)
        self.list_View.setSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.MinimumExpanding)
        
        loadDataBase_Button = QPushButton(self.tr("载入数据库"))
        loadDataBase_Button.resize(75, 35)
        loadDataBase_Button.setSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
        chooseKeyword_Button = QPushButton(self.tr("选择关键字"))
        chooseKeyword_Button.resize(75, 35)
        chooseKeyword_Button.setSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
#         export_Button = QPushButton(self.tr("导出"))
#         export_Button.resize(75, 35)
#         export_Button.setSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
        sub_Layout = QVBoxLayout()        
        sub_Layout.addWidget(loadDataBase_Button)
        sub_Layout.addWidget(chooseKeyword_Button)
#         sub_Layout.addWidget(export_Button)
        main_layout = QHBoxLayout()
        main_layout.addWidget(self.data_Group)
        main_layout.addLayout(sub_Layout)
        
        self.setLayout(main_layout)

        self.connect(loadDataBase_Button, SIGNAL("clicked()"), self.loadDataBase)
        self.connect(chooseKeyword_Button, SIGNAL("clicked()"), self.chooseKeyword)
#         self.connect(export_Button, SIGNAL("clicked()"), GetData)
        
        self.SQL_list = QStringList()
        self.SQL_list_backup = QStringList()
        self.keyword_list = []
        self.startY = 0
        self.endY = 0

    def loadDataBase(self):
        self.SQL_list = QFileDialog.getOpenFileNames(self, self.tr("选择数据库"), "./", "DB (*.mdb)")
        self.list_View.clear()
        self.list_View.addItems(self.SQL_list)
#         self.SQL_list = QStringList()
#         self.SQL_list.append(QString("E:\\baoshan.mdb"))
        
    def chooseKeyword(self):
        if self.SQL_list:
            for x in self.SQL_list:
                self.SQL_list_backup.append(x)
            print "before subdialog"
            print self.SQL_list.count()
            print self.SQL_list_backup.count()
            subdialog = SubDialog(self.SQL_list)
            print  "after subdialog"
            print self.SQL_list.count()
            print self.SQL_list_backup.count()
            subdialog.sendData_signal.connect(self.GetKeyword)
            subdialog.setModal(True)
            subdialog.exec_()
            
    def GetData(self, keyword_list, startY, endY):
        print "start print Data"
        
        for x in keyword_list:
            print keyword_list
        
        print self.SQL_list_backup.count()
        for xx in range(self.SQL_list_backup.count()):
            conn = win32com.client.Dispatch(r'ADODB.Connection')
            name = self.SQL_list_backup.takeAt(xx)
            name_1 = copy.deepcopy(name)
            name_1 = str(name_1.split(".").takeAt(0) + '.doc')
            DSN = 'PROVIDER = Microsoft.Jet.OLEDB.4.0;DATA SOURCE=' + name + ';'
            conn.Open(DSN)
            print "connect established"
            
            rs = win32com.client.Dispatch(r'ADODB.Recordset')
            rs_name = 'table'
            rs.Open('[' + rs_name + ']', conn, 1, 3)
            rs.MoveFirst()

            recode = []
            result_in = []
            result_out = []
            
            while not rs.EOF:
                print "level 1"
                line = rs.Fields.Item(1).Value
                recode.append(line)
                item_1 = rs.Fields.Item(2).Value
                item_2 = rs.Fields.Item(3).Value
                item_3 = rs.Fields.Item(4).Value
                local = rs.Fields.Item(5).Value
                bg_yr = rs.Fields.Item(6).Value
                end_yr = rs.Fields.Item(7).Value
                bg_reason = rs.Fields.Item(8).Value
                end_reason = rs.Fields.Item(9).Value
                district = rs.Fields.Item(10).Value
                data_con = rs.Fields.Item(11).Value
                compiler = rs.Fields.Item(12).Value
                check_data = rs.Fields.Item(13).Value
                note = rs.Fields.Item(14).Value
                    
                print "this is item_3"
                if item_3:
                    print QString(item_3)
                    for x in keyword_list:
                        print x
                        print "this is by_yr and startY"
                        print bg_yr
                        print startY
                        if x == QString(item_3):
                            if bg_yr > startY and bg_yr <= endY:
                                print item_2, item_3, local, bg_yr, end_yr, bg_reason, end_reason, district, data_con, compiler, check_data, note
                                if type(item_1) is types.UnicodeType:   item_1 = item_1.decode('utf-8')
                                if type(item_2) is types.UnicodeType:   item_2 = item_2.decode('utf-8')
                                if type(item_3) is types.UnicodeType:   item_3 = item_3.decode('utf-8')
                                if type(local) is types.UnicodeType:   local = local.decode('utf-8')
                                if type(bg_yr) is types.IntType:   bg_yr = unicode(bg_yr)
                                if type(end_yr) is types.IntType:   end_yr = unicode(end_yr)
                                if type(bg_reason) is types.UnicodeType:   bg_reason = bg_reason.decode('utf-8')
                                if type(end_reason) is types.UnicodeType:   end_reason = end_reason.decode('utf-8')
                                if type(district) is types.UnicodeType:   district = district.decode('utf-8')
                                if type(data_con) is types.IntType:   data_con = unicode(data_con)
                                if type(compiler) is types.UnicodeType:   compiler = compiler.decode('utf-8')
                                if type(check_data) is types.MemberDescriptorType:   check_data = unicode(check_data)
                                if type(note) is types.UnicodeType:   note = note.decode('utf-8')
                                       
                                result_in.append(unicode('\r\n'))  
                                result_in.append(unicode('\r\n'))  
                                result_in.append(note)
                                result_in.append(unicode('\r\n'))
                                result_in.append(check_data)
                                result_in.append(unicode(u'审核时间：'))
                                result_in.append(unicode('\r\n'))            
                                result_in.append(compiler)
                                result_in.append(unicode(u'审核人：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(data_con)
                                result_in.append(unicode(u'审核次数：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(district)
                                result_in.append(unicode(u'区域：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(end_reason)
                                result_in.append(unicode(u'拆迁原因：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(bg_reason)
                                result_in.append(unicode(u'建立原因：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(end_yr)
                                result_in.append(unicode(u'拆迁年份：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(bg_yr)
                                result_in.append(unicode(u'建立年份：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(local)
                                result_in.append(unicode(u'地址：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(item_3)
                                result_in.append(unicode(u'类别2：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(item_2)
                                result_in.append(unicode(u'类别1'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(item_1)
                                result_in.append(unicode(u'现状：'))
                                result_in.append(unicode('\r\n'))  
                                result_in.append(line)
                                result_in.append(unicode(u'单位名称:'))
                                   
                rs.MoveNext()
            print '=========================================='
            conn.Close()
            for x in result_in:
                print x
                
            w = win32com.client.Dispatch('Word.Application')
            #w.Visiable = 0
            w.DisplayAlerts = 0
            doc = w.Documents.Add()
            myRange = doc.Range(0, 0)
            
            for x in result_in:
                myRange.InsertBefore(x)
            
            doc.SaveAs(name_1)  
            doc.Close()
        print "leave DB"

    @QtCore.pyqtSlot(QStringList, QString, QString)
    def GetKeyword(self, keyword_list, startY, endY):
        print "now get the keyword"
        for x in keyword_list:
            print x
            self.keyword_list.append(x)
        self.startY = (startY.toInt())[0]
        self.endY = (endY.toInt())[0]
        self.GetData(self.keyword_list, self.startY, self.endY)
        for x in self.keyword_list:
            print x

#继承得来的CheckBox类，适用于动态分配的CheckBox传递它的title
class CheckBox(QCheckBox):
    pressed = QtCore.pyqtSignal(QString)
    def __init__(self, string, parent = None):
        super(CheckBox, self).__init__(string, parent)
        self.title = string
        self.connect(self, SIGNAL("clicked()"), self.helperFun)

    @QtCore.pyqtSlot()
    def helperFun(self):
        self.pressed.emit(self.title)

#模式对话框是否有返回值，若有返回值，则可以返回一个列表进行分析，目前方案是通过信号槽
class SubDialog(QDialog):
    sendData_signal = QtCore.pyqtSignal(QStringList, QString, QString)
    def __init__(self, SQL_list, parent = None):
        super(SubDialog, self).__init__(parent)
        
        self.setWindowTitle("Please Choose tags")
        category_Label = QLabel(self.tr("类别"))
        startTime_Lable = QLabel(self.tr("起始年"))
        endTime_Label = QLabel(self.tr("终止年"))
        self.startTime_LineEdit = QLineEdit("1900")
        self.endTime_LineEdit = QLineEdit("2000")
        confirm_Button = QPushButton(self.tr("确认"))
        cancel_Button = QPushButton(self.tr("关闭"))
        self.tag_list = []
        self.key_list = QStringList()
        
        recode = {}
        for x in range(SQL_list.count()):
            conn = win32com.client.Dispatch(r'ADODB.Connection')
            DSN = 'PROVIDER = Microsoft.Jet.OLEDB.4.0;DATA SOURCE=' + SQL_list.takeAt(x) + ';'
            conn.Open(DSN)
            
            rs = win32com.client.Dispatch(r'ADODB.Recordset')
            rs_name = 'table'
            rs.Open('[' + rs_name + ']', conn, 1, 3)
            rs.MoveFirst()


            while not rs.EOF:
                line = rs.Fields.Item(4).Value
                if line:
                    line.encode('utf8')
                recode[line] = 0
                rs.MoveNext() 
                
#             for x in range(recode.__len__()):
#                 print recode.keys()[x]
            conn.Close()
        keys = recode.keys()

        Gridlayout = QGridLayout()
        for x in range(keys.__len__()):
            if  keys[x]:
                checkBox = CheckBox(keys[x])
                Gridlayout.addWidget(checkBox, x / 5 , x % 5 + 1, 1, 1)
                checkBox.pressed.connect(self.addToList)
        Gridlayout.addWidget(category_Label, 0, 0, 1, 1)
        Gridlayout.addWidget(startTime_Lable, keys.__len__() / 5 + 1, 0, 3, 1)
        Gridlayout.addWidget(endTime_Label, keys.__len__() / 5 + 4, 0, 3, 1)
        Gridlayout.addWidget(self.startTime_LineEdit, keys.__len__() / 5 + 1, 1, 3, 2)
        Gridlayout.addWidget(self.endTime_LineEdit, keys.__len__() / 5 + 4, 1, 3, 2)
        Gridlayout.addWidget(confirm_Button, keys.__len__() / 5 + 7, 4, 1, 1)
        Gridlayout.addWidget(cancel_Button, keys.__len__() / 5 + 7, 5, 1, 1)
        
        self.setLayout(Gridlayout)
        
        self.connect(confirm_Button, SIGNAL("clicked()"), self.sendData)
        self.connect(cancel_Button, SIGNAL("clicked()"), self.close)
        
    def sendData(self):
        for x in self.tag_list:
#             print x
            self.key_list.append(x)
        startY = self.startTime_LineEdit.text()
        endY = self.endTime_LineEdit.text()
        print "before emit"
        self.sendData_signal.emit(self.key_list, startY, endY)
        print "after emit"
        self.close()
    
    def addToList(self, tag):
        if  not self.tag_list.count(tag):
            self.tag_list.append(tag)
        else:
            self.tag_list.remove(tag)
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = MainDialog()
    form.show()
    app.exec_()