TEMPLATE = subdirs

SUBDIRS += \
    Model \
    Desktop

Desktop.depends = Model
