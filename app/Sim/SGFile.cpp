#include "SGFile.h"

SGFile::SGFile(QObject *parent)
    : QObject{parent}
{

}


QString SGFile::saveFile(QList<SGModelBase*> itemList)
{
    QJsonArray array;
    
    for(SGModelBase* Model : itemList) {
        QJsonObject obj = Model->convertToJson();
        array.append(obj);
    }
    
    QJsonObject obj_re;
    obj_re.insert("array", array);
    
    return QString(QJsonDocument(obj_re).toJson());
}

QList<SGModelBase*> SGFile::loadFile(QString jsonFileContent)
{
    QList<SGModelBase*> listBase;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileContent.toLocal8Bit().data());
    if(!jsonDocument.isNull())
    {
        QJsonObject jsonObject = jsonDocument.object();
        QJsonValue jsonValue = jsonObject.value("array");
        if (!jsonValue.isNull())
        {
            QJsonArray array_content = jsonValue.toArray();
            for(int i=0; i<array_content.count(); i++) {
                QJsonObject obj_Model = array_content.at(i).toObject();
                
                SGItemType obj_type = (SGItemType)obj_Model.value("type").toInt();
                SGModelBase* ModelBase = createModelBase(obj_type);
                
                ModelBase->loadFromJson(obj_Model);
                listBase.append(ModelBase);
            }
        }
    }
    else
    {
        qDebug()<< "SLS Json File Parse ERROR.";
    }
    
    return listBase;
}

SGModelBase* SGFile::createModelBase(SGItemType itemType)
{
    SGModelBase* ModelBase;
    switch (itemType) {
        case SGItemType::ItemTypeResistance:
            ModelBase = new SGModelRes();
            break;
        case SGItemType::ItemTypeGround:
            ModelBase = new SGModelGround();
            break;
        case SGItemType::ItemTypeSourceA:
            ModelBase = new SGModelSource(SGModelSourceType::SourceTypeA);
            break;
        case SGItemType::ItemTypeSourceV:
            ModelBase = new SGModelSource(SGModelSourceType::SourceTypeV);
            break;
        case SGItemType::ItemTypeLine:
            ModelBase = new SGModelLine();
            break;
        default:
            break;
    }
    return ModelBase;
}
