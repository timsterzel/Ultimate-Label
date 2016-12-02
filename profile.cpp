#include "profile.h"

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

void Profile::writeToJson(QJsonObject &json)
{
    json[JSON_NAME] = m_name;
    json[JSON_SEPERATOR] = m_seperator;
    json[JSON_TEMPLATETEXT] = m_templateText;
}

void Profile::readFromJson(QJsonObject &json) const
{
    m_name = json[JSON_NAME].toString();
    m_seperator = json[JSON_SEPERATOR].toString();
    m_templateText = json[JSON_TEMPLATETEXT].toString();

}
