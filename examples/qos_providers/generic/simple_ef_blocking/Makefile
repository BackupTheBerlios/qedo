# Qedo - Quality of Service Enabled Distributed Objects
#
# http://qedo.berlios.de/
#
# Copyright (C) 2002-2003 by the Qedo Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

.NOTPARALLEL:

SUBDIRS = EventFrequency_EFQoSProviderComposition_SERVANT \
	EventFrequency_EFQoSProviderComposition \


all: MakeComponentVars $(SUBDIRS:%=%-all)

clean: $(SUBDIRS:%=%-clean)


%-all: %
	$(MAKE) -C $< all


MakeComponentVars:
	cp ${QEDO}/etc/MakeComponentVars .

%-clean: %
	$(MAKE) -C $< clean

package:
	$(MAKE) -C EventFrequency_EFQoSProviderComposition package

assembly: package
	$(MAKE) -C chat_with_EF_linux_assembly
