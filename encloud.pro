include(common.pri)

TEMPLATE = subdirs

SUBDIRS += src

# init script used only on linux
unix {
    SUBDIRS += etc
}

# tests depend on build
check.depends = all

# generate tar package
TARFILE = $${PKGNAME_LOWER}-$${VERSION}.tar
TARZIPFILE = $${TARFILE}.gz
dist.target = dist
dist.commands = @( \
                echo "Making tar package $${TARZIPFILE}"; \
                if [ -e .svn ]; then \
                    echo "found VCS: SVN"; \
                    find . -type f -not -iwholename '*.svn*' | \
                    xargs svn status -v 2>/dev/null | grep -v "^[?I]" | \
                    sed 's,^\\ ,-,' | sed 's,A*+,,' | \
                    tr -s "[:space:]" | cut -d '\\ ' -f 5 | \
                    xargs tar czf .$${TARZIPFILE}; \
                elif [ -e .git ]; then \
                    echo "found VCS: GIT"; \
                    git rev-parse --short HEAD > .revision; \
                    tar cf .$${TARFILE} .revision; \
                    git ls-files | xargs tar rf .$${TARFILE}; \
                    gzip .$${TARFILE}; \
                else \
                    echo "[warn] no VCS found"; \
                    # not under VCS \
                    find . -type f -not -name Makefile | \
                    xargs tar czf .$${TARZIPFILE}; \
                fi ; \
                rm -rf $${PKGNAME_LOWER}-$${VERSION}; \
                mkdir $${PKGNAME_LOWER}-$${VERSION}; \
                tar xzf .$${TARZIPFILE} -C $${PKGNAME_LOWER}-$${VERSION}; \
                tar czvf $${TARZIPFILE} $${PKGNAME_LOWER}-$${VERSION}; \
                md5sum $${TARZIPFILE} > $${TARZIPFILE}.md5; \
                rm -rf .$${TARZIPFILE}; \
                )
QMAKE_EXTRA_TARGETS += dist

# override distclean so we can remove extra files
redirect_distclean.target = distclean
redirect_distclean.commands = rm -rf Makefile $${PKGNAME_LOWER}-$${VERSION}*
QMAKE_EXTRA_TARGETS += redirect_distclean
