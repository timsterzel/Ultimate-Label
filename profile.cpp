#include "profile.h"

const QString Profile::JSON_NAME{ "name" };
const QString Profile::JSON_SEPERATOR{ "seperator" };
const QString Profile::JSON_CODEC{ "codec" };
const QString Profile::JSON_CONTAINSHEADER{ "containsHeader" };
const QString Profile::JSON_TEMPLATETEXT{ "templateText" };

Profile::Profile()
{

}

Profile::Profile(QString name, QString seperator, QString codec, bool containsHeader, QString templateText)
: m_name{ name }
, m_seperator{ seperator }
, m_codec{ codec }
, m_containsHeader{ containsHeader }
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

QString Profile::getCodec() const
{
    return m_codec;
}

void Profile::setCodec(QString codec)
{
    m_codec = codec;
}

bool Profile::containsHeader() const
{
    return m_containsHeader;
}

void Profile::setContainsHeader(bool containsHeader)
{
    m_containsHeader = containsHeader;
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
    json.insert(JSON_CODEC, m_codec);
    json.insert(JSON_CONTAINSHEADER, m_containsHeader);
    json.insert(JSON_TEMPLATETEXT, m_templateText);
}

void Profile::readFromJson(QJsonObject &json)
{
    m_name = json.value(JSON_NAME).toString();
    m_seperator = json.value(JSON_SEPERATOR).toString();
    m_codec = json.value(JSON_CODEC).toString();
    m_containsHeader = json.value(JSON_CONTAINSHEADER).toBool();
    m_templateText = json.value(JSON_TEMPLATETEXT).toString();
}
