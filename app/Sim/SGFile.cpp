#include "SGFile.h"

SGFile::SGFile(QObject *parent)
    : QObject{parent}
{

}


QString SGFile::saveFile(QList<SGModalBase*> itemList)
{
    QJsonArray array;
    
    for(SGModalBase* modal : itemList) {
        QJsonObject obj = modal->convertToJson();
        array.append(obj);
    }
    
    QJsonObject obj_re;
    obj_re.insert("array", array);
    
    return QString(QJsonDocument(obj_re).toJson());
}

QList<SGModalBase*> SGFile::loadFile(QString jsonFileContent)
{
    QList<SGModalBase*> listBase;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileContent.toLocal8Bit().data());
    if(!jsonDocument.isNull())
    {
        QJsonObject jsonObject = jsonDocument.object();
        QJsonValue jsonValue = jsonObject.value("array");
        if (!jsonValue.isNull())
        {
            QJsonArray array_content = jsonValue.toArray();
            for(int i=0; i<array_content.count(); i++) {
                QJsonObject obj_modal = array_content.at(i).toObject();
                
                SGItemType obj_type = (SGItemType)obj_modal.value("type").toInt();
                SGModalBase* modalBase = createModalBase(obj_type);
                
                modalBase->loadFromJson(obj_modal);
                listBase.append(modalBase);
            }
        }
    }
    else
    {
        qDebug()<< "SLS Json File Parse ERROR.";
    }
    
    return listBase;
}

SGModalBase* SGFile::createModalBase(SGItemType itemType)
{
    SGModalBase* modalBase;
    switch (itemType) {
        case SGItemType::ItemTypeResistance:
            modalBase = new SGModalRes();
            break;
        case SGItemType::ItemTypeGround:
            modalBase = new SGModalGround();
            break;
        case SGItemType::ItemTypeSourceA:
            modalBase = new SGModalSource(SGModalSourceType::SourceTypeA);
            break;
        case SGItemType::ItemTypeSourceV:
            modalBase = new SGModalSource(SGModalSourceType::SourceTypeV);
            break;
        case SGItemType::ItemTypeLine:
            modalBase = new SGModalLine();
            break;
        default:
            break;
    }
    return modalBase;
}
