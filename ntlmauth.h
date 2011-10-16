#ifndef NTLMAUTH_H
#define NTLMAUTH_H

#include <windows.h>

#define SECURITY_WIN32
#include <security.h>

#include <interfaces/ixmppstreams.h>

class NtlmAuth : 
	public QObject,
	public IXmppFeature,
	public IXmppStanzaHadler
{
	Q_OBJECT;
	Q_INTERFACES(IXmppFeature IXmppStanzaHadler);
public:
	NtlmAuth(IXmppStream *AXmppStream);
	~NtlmAuth();
	virtual QObject *instance() { return this; }
	//IXmppStanzaHadler
	virtual bool xmppStanzaIn(IXmppStream *AXmppStream, Stanza &AStanza, int AOrder);
	virtual bool xmppStanzaOut(IXmppStream *AXmppStream, Stanza &AStanza, int AOrder);
	//IXmppFeature
	virtual QString featureNS() const;
	virtual IXmppStream *xmppStream() const;
	virtual bool start(const QDomElement &AElem);
signals:
	void finished(bool ARestart);
	void error(const QString &AError);
	void featureDestroyed();
private:
	IXmppStream *FXmppStream;
private:
	CredHandle FCredHandle;
	CtxtHandle FCtxtHandle;
	PSecPkgInfo FSecPackInfo;
	SEC_WINNT_AUTH_IDENTITY FIdentity;
};

#endif // NTLMAUTH_H
