/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "rescuableartifactdata.h"

#include "command.h"

#include <tools/persistence.h>

namespace qbs {
namespace Internal {

RescuableArtifactData::~RescuableArtifactData()
{
}

void RescuableArtifactData::load(PersistentPool &pool)
{
    pool.stream() >> timeStamp;

    int c;
    pool.stream() >> c;
    for (int i = 0; i < c; ++i) {
        ChildData cd;
        cd.productName = pool.idLoadString();
        cd.productProfile = pool.idLoadString();
        cd.childFilePath = pool.idLoadString();
        pool.stream() >> cd.addedByScanner;
        children << cd;
    }

    commands = loadCommandList(pool);
}

void RescuableArtifactData::store(PersistentPool &pool) const
{
    pool.stream() << timeStamp;

    pool.stream() << children.count();
    foreach (const ChildData &cd, children) {
        pool.storeString(cd.productName);
        pool.storeString(cd.productProfile);
        pool.storeString(cd.childFilePath);
        pool.stream() << cd.addedByScanner;
    }

    storeCommandList(commands, pool);
}

} // namespace Internal
} // namespace qbs
