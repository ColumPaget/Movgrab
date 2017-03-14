

AC_INIT([main.c])

VERSION="1.2.1" 
AC_SUBST(VERSION) 

AC_CONFIG_SUBDIRS([libUseful-2.6])

AC_PROG_CC 
AC_LANG_C 
AC_PROG_MAKE_SET 
AC_PROG_INSTALL 
AC_HEADER_STDC 

AC_CHECK_LIB(z,deflate,,)
cf_have_libz=$ac_cv_lib_z_deflate

AC_ARG_ENABLE(largefiles, [  --enable-largefiles       enable largefile support], cf_use_largefiles=$enableval )
AC_ARG_ENABLE(ssl, [  --enable-ssl       use Secure Sockets Layer], cf_use_ssl=$enableval )

if test "$cf_use_largefiles" != "no" 
then
AC_DEFINE([_LARGEFILE64_SOURCE])
AC_DEFINE([_FILE_OFFSET_BITS],[64])
fi

if test "$cf_use_ssl" = "yes" 
then
AC_CHECK_LIB(ssl,SSL_library_init,,)
cf_have_libssl=$ac_cv_lib_ssl_SSL_library_init

AC_CHECK_LIB(crypto,EVP_CIPHER_CTX_init,,)
cf_have_libcrypto=$ac_cv_lib_crypto_EVP_CIPHER_CTX_init
fi


dnl read Makefile.in and write Makefile 
AC_OUTPUT(Makefile)

echo
echo "********** Movgrab Settings *********"
if test	"$cf_have_libssl" != "yes" 
then
echo "SSL/https NOT enabled"
else
echo "SSL and https enabled"
fi

if test	"$cf_use_largefiles" = "no" 
then
echo "Largefiles NOT enabled"
else
echo "Largefiles enabled"
fi


