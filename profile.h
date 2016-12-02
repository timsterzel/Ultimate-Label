#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <QJsonObject>

class Profile
{
private:
    // Strings which are used for reading and writing Json files
    static const QString JSON_NAME = "name";
    static const QString JSON_SEPERATOR = "seperator";
    static const QString JSON_TEMPLATETEXT = "templateText";

    QString m_name;
    QString m_seperator;
    QString m_templateText;
public:
    Profile();
    Profile(QString name, QString seperator, QString templateText);

    QString getName() const;
    void setName(QString name);

    QString getSeperator() const;
    void setSeperator(QString seperator);

    QString getTemplateText() const;
    void setTemplateText(QString templateText);

    void writeToJson(QJsonObject &json);
    void readFromJson(QJsonObject &json) const;
}

#endif // PROFILE_H
