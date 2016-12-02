#include "profile.h"

const QString Profile::JSON_NAME = "name";
const QString Profile::JSON_SEPERATOR = "seperator";
const QString Profile::JSON_TEMPLATETEXT = "templateText";

Profile::Profile()
{

}

Profile::Profile(QString name, QString seperator, QString templateText)
: m_name{ name }
, m_seperator{ seperator }
, m_templateText{ templateText }
{

}

QString Profile::getName() const
{
    return m_name;
}

void Profile::setName(QString name)
{
    m_name = name;
}

QString Profile::getSeperator() const
{
    return m_seperator;
}

void Profile::setSeperator(QString seperator)
{
    m_seperator = seperator;
}

QString Profile::getTemplateText() const
{
    return m_templateText;
}

void Profile::setTemplateText(QString templateText)
{
    m_templateText = templateText;
}

void Profile::writeToJson(QJsonObject &json) const
{
    json.insert(JSON_NAME, m_name);
    json.insert(JSON_SEPERATOR, m_seperator);
    json.insert(JSON_TEMPLATETEXT, m_templateText);
}

void Profile::readFromJson(QJsonObject &json)
{
    m_name = json.value(JSON_NAME).toString();
    m_seperator = json.value(JSON_SEPERATOR).toString();
    m_templateText = json.value(JSON_TEMPLATETEXT).toString();
}
