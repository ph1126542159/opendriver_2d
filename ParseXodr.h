#ifndef PARSEXODR_H
#define PARSEXODR_H
#include "Plugin/tessplugin.h"
#include <QObject>
class XodrNet;
class XodrSimulator;
class ParseXodr: public QObject,public TessPlugin
{
    Q_OBJECT
public:
    explicit ParseXodr(QObject* parent=nullptr);

    void init() override;
    void unload() override;

    CustomerGui *customerGui() override;

    CustomerNet *customerNet() override;

    CustomerSimulator *customerSimulator() override;
private:
    std::shared_ptr<XodrNet> m_ptrXodrNet;
    std::shared_ptr<XodrSimulator> m_ptrXodrSimu;
    void initGui();
};

#endif // PARSEXODR_H
