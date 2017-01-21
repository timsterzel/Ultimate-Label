#ifndef PROFILE_H
#define PROFILE_H
#include <QJsonObject>
#include <QString>

class Profile
{
private:
    // Identifier for Json file
    static const QString JSON_NAME;
    static const QString JSON_SEPERATOR;
    static const QString JSON_CODEC;
    static const QString JSON_CONTAINSHEADER;
    static const QString JSON_TEMPLATETEXT;

    QString m_name;    
    QString m_seperator;
    QString m_codec;
    bool m_containsHeader;
    QString m_templateText;
public:
    Profile();
    Profile(QString name, QString seperator, QString codec, bool containsHeader, QString templateText);

    QString getName() const;
    void setName(QString name);

    QString getSeperator() const;
    void setSeperator(QString seperator);

    QString getCodec() const;
    void setCodec(QString codec);

    bool containsHeader() const;
    void setContainsHeader(bool containsHeader);

    QString getTemplateText() const;
    void setTemplateText(QString templateText);

    void writeToJson(QJsonObject &json) const;
    void readFromJson(QJsonObject &json);
};

#endif // PROFILE_H
