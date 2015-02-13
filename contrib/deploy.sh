#!/bin/sh -x
#
# Deploy ECE/SECE files based on local installation.
# (DEVELOPMENT ONLY)

[ -z ${MODE} ] && MODE="ece"
[ -z ${HOST} ] && HOST="192.168.122.132"

# copy global libencloud settings (for license)
[ "${MODE}" = "sece" ] && scp /etc/xdg/Exor/libencloud.conf usom:/etc/qt4/Exor/libencloud.conf

# copy initialization certificates
ssh usom sudo mkdir -p /var/lib/encloud
rsync -a --rsync-path="sudo rsync" /var/lib/encloud/init* usom:/var/lib/encloud/

# copy switchboard host and restart service
ssh usom "sudo /etc/init.d/encloud restart; \
        grep switchboard-host /etc/hosts 2>/dev/null || \
            echo "${HOST} switchboard-host" | sudo tee -a /etc/hosts"
