#include "qvkimplatforminputcontext.h"

#include <qpa/qplatforminputcontextplugin_p.h>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QVkImPlatformInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "vkim.json")

public:
    QVkImPlatformInputContext *create(const QString&, const QStringList&) Q_DECL_OVERRIDE;
};

QVkImPlatformInputContext *QVkImPlatformInputContextPlugin::create(const QString& system, const QStringList& paramList)
{
    Q_UNUSED(paramList);

    if (system == QLatin1String("vkim")) {
        return new QVkImPlatformInputContext;
    }

    return 0;
}

QT_END_NAMESPACE

#include "main.moc"
