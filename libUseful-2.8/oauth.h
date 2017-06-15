#ifndef LIBUSEFUL_OAUTH_H
#define LIBUSEFUL_OAUTH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"

void OAuthDeviceLogin(char *LoginURL, char *ClientID, char *Scope, char **DeviceCode, char **UserCode, char **NextURL);
void OAuthDeviceGetAccessToken(char *TokenURL, char *ClientID, char *ClientSecret, char *DeviceCode, char **AccessToken, char **RefreshToken);
void OAuthDeviceRefreshToken(char *TokenURL, char *ClientID, char *ClientSecret, char *RequestRefreshToken, char **AccessToken, char **RefreshToken);
void OAuthInstalledAppGetAccessToken(char *TokenURL, char *ClientID, char *ClientSecret, char *AuthCode, char *RedirectURL, char **AccessToken, char **RefreshToken);

char *OAuthFormatLoginURL(char *RetStr, const char *LoginURL, const char *ClientID, const char *Scope, const char *RedirectURL);

char *OAuthGetAccessToken(char *RetStr, const char *URL, const char *Key, const char *RequestToken);
char *OAuthGetRequestToken(char *RetStr, const char *URL, const char *Key, const char *RedirectURL);
#ifdef __cplusplus
}
#endif

#endif

