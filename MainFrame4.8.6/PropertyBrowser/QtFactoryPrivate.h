#ifndef QTFACTORYPRIVATE_H
#define QTFACTORYPRIVATE_H

#include <QtGui/QSpinBox>
#include <QtGui/QScrollBar>
#include <QtGui/QComboBox>
#include <QtGui/QAbstractItemView>
#include <QtGui/QLineEdit>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMenu>
#include <QtGui/QKeyEvent>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QColorDialog>
#include <QtGui/QFontDialog>
#include <QtGui/QSpacerItem>
#include <QtGui/QStyleOption>
#include <QtGui/QPainter>
#include <QtCore/QMap>
#include <QFontDatabase>
//#include <QtCursorDatabase>

#include "qtpropertybrowserutils_p.h"

// ---------- EditorFactoryPrivate :
// Base class for editor factory private classes. Manages mapping of properties to editors and vice versa.

template <class Editor>
class EditorFactoryPrivate
{
public:

	typedef QList<Editor *> EditorList;
	typedef QMap<QtProperty *, EditorList> PropertyToEditorListMap;
	typedef QMap<Editor *, QtProperty *> EditorToPropertyMap;

	Editor *createEditor(QtProperty *property, QWidget *parent);
	void initializeEditor(QtProperty *property, Editor *e);
	void slotEditorDestroyed(QObject *object);

	PropertyToEditorListMap  m_createdEditors;
	EditorToPropertyMap m_editorToProperty;
};

template <class Editor>
Editor *EditorFactoryPrivate<Editor>::createEditor(QtProperty *property, QWidget *parent)
{
	Editor *editor = new Editor(parent);
	initializeEditor(property, editor);
	return editor;
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeEditor(QtProperty *property, Editor *editor)
{
	Q_TYPENAME PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
	if (it == m_createdEditors.end())
		it = m_createdEditors.insert(property, EditorList());
	it.value().append(editor);
	m_editorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject *object)
{
	const Q_TYPENAME EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
	for (Q_TYPENAME EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
		if (itEditor.key() == object) {
			Editor *editor = itEditor.key();
			QtProperty *property = itEditor.value();
			const Q_TYPENAME PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
			if (pit != m_createdEditors.end()) {
				pit.value().removeAll(editor);
				if (pit.value().empty())
					m_createdEditors.erase(pit);
			}
			m_editorToProperty.erase(itEditor);
			return;
		}
	}
}


template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
	data->minVal = minVal;
	if (data->maxVal < data->minVal)
		data->maxVal = data->minVal;

	if (data->val < data->minVal)
		data->val = data->minVal;
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
	data->maxVal = maxVal;
	if (data->minVal > data->maxVal)
		data->minVal = data->maxVal;

	if (data->val > data->maxVal)
		data->val = data->maxVal;
}

template <class PrivateData, class Value>
static void setSizeMinimumData(PrivateData *data, const Value &newMinVal)
{
	data->minVal = newMinVal;
	if (data->maxVal.width() < data->minVal.width())
		data->maxVal.setWidth(data->minVal.width());
	if (data->maxVal.height() < data->minVal.height())
		data->maxVal.setHeight(data->minVal.height());

	if (data->val.width() < data->minVal.width())
		data->val.setWidth(data->minVal.width());
	if (data->val.height() < data->minVal.height())
		data->val.setHeight(data->minVal.height());
}

template <class PrivateData, class Value>
static void setSizeMaximumData(PrivateData *data, const Value &newMaxVal)
{
	data->maxVal = newMaxVal;
	if (data->minVal.width() > data->maxVal.width())
		data->minVal.setWidth(data->maxVal.width());
	if (data->minVal.height() > data->maxVal.height())
		data->minVal.setHeight(data->maxVal.height());

	if (data->val.width() > data->maxVal.width())
		data->val.setWidth(data->maxVal.width());
	if (data->val.height() > data->maxVal.height())
		data->val.setHeight(data->maxVal.height());
}

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
	SizeValue croppedVal = val;
	if (minVal.width() > val.width())
		croppedVal.setWidth(minVal.width());
	else if (maxVal.width() < val.width())
		croppedVal.setWidth(maxVal.width());

	if (minVal.height() > val.height())
		croppedVal.setHeight(minVal.height());
	else if (maxVal.height() < val.height())
		croppedVal.setHeight(maxVal.height());

	return croppedVal;
}

// ------------ QtSpinBoxFactory
class QtSpinBoxFactory;
class QtSpinBoxFactoryPrivate : public EditorFactoryPrivate<QSpinBox>
{
	QtSpinBoxFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtSpinBoxFactory)
public:

	void slotPropertyChanged(QtProperty *property, int value);
	void slotRangeChanged(QtProperty *property, int min, int max);
	void slotSingleStepChanged(QtProperty *property, int step);
	void slotSetValue(int value);
};

// QtDoubleSpinBoxFactory
class QtDoubleSpinBoxFactory;
class QtDoubleSpinBoxFactoryPrivate : public EditorFactoryPrivate<QDoubleSpinBox>
{
	QtDoubleSpinBoxFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtDoubleSpinBoxFactory)
public:

	void slotPropertyChanged(QtProperty *property, double value);
	void slotRangeChanged(QtProperty *property, double min, double max);
	void slotSingleStepChanged(QtProperty *property, double step);
	void slotDecimalsChanged(QtProperty *property, int prec);
	void slotSetValue(double value);
};

// QtCheckBoxFactory
class QtCheckBoxFactory;
class QtCheckBoxFactoryPrivate : public EditorFactoryPrivate<QtBoolEdit>
{
	QtCheckBoxFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtCheckBoxFactory)
public:
	void slotPropertyChanged(QtProperty *property, bool value);
	void slotSetValue(bool value);
};

// QtSliderFactory
class QtScrollBarFactory;
class QtScrollBarFactoryPrivate : public  EditorFactoryPrivate<QScrollBar>
{
	QtScrollBarFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtScrollBarFactory)
public:
	void slotPropertyChanged(QtProperty *property, int value);
	void slotRangeChanged(QtProperty *property, int min, int max);
	void slotSingleStepChanged(QtProperty *property, int step);
	void slotSetValue(int value);
};


// QtColorPropertyManager
class QtColorPropertyManager;
class QtIntPropertyManager;

class QtColorPropertyManagerPrivate
{
	QtColorPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtColorPropertyManager)
public:

	void slotIntChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);

	typedef QMap<const QtProperty *, QColor> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToR;
	QMap<const QtProperty *, QtProperty *> m_propertyToG;
	QMap<const QtProperty *, QtProperty *> m_propertyToB;
	QMap<const QtProperty *, QtProperty *> m_propertyToA;

	QMap<const QtProperty *, QtProperty *> m_rToProperty;
	QMap<const QtProperty *, QtProperty *> m_gToProperty;
	QMap<const QtProperty *, QtProperty *> m_bToProperty;
	QMap<const QtProperty *, QtProperty *> m_aToProperty;
};

// QtDateTimeEditFactory
class QtDateTimeEditFactory;
class QtDateTimeEditFactoryPrivate : public EditorFactoryPrivate<QDateTimeEdit>
{
	QtDateTimeEditFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtDateTimeEditFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QDateTime &value);
	void slotSetValue(const QDateTime &value);

};


// QtSliderFactory
class QtSliderFactory;
class QtSliderFactoryPrivate : public EditorFactoryPrivate<QSlider>
{
	QtSliderFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtSliderFactory)
public:
	void slotPropertyChanged(QtProperty *property, int value);
	void slotRangeChanged(QtProperty *property, int min, int max);
	void slotSingleStepChanged(QtProperty *property, int step);
	void slotSetValue(int value);
};

// QtLineEditFactory
class QtLineEditFactory;
class QtLineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit>
{
	QtLineEditFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtLineEditFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QString &value);
	void slotRegExpChanged(QtProperty *property, const QRegExp &regExp);
	void slotSetValue(const QString &value);
};

// QtDateEditFactory
class QtDateEditFactory;
class QtDateEditFactoryPrivate : public EditorFactoryPrivate<QDateEdit>
{
	QtDateEditFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtDateEditFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QDate &value);
	void slotRangeChanged(QtProperty *property, const QDate &min, const QDate &max);
	void slotSetValue(const QDate &value);
};

// QtTimeEditFactory
class QtTimeEditFactory;
class QtTimeEditFactoryPrivate : public EditorFactoryPrivate<QTimeEdit>
{
	QtTimeEditFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtTimeEditFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QTime &value);
	void slotSetValue(const QTime &value);
};

// QtKeySequenceEditorFactory
class QtKeySequenceEditorFactory;
class QtKeySequenceEditorFactoryPrivate : public EditorFactoryPrivate<QtKeySequenceEdit>
{
	QtKeySequenceEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtKeySequenceEditorFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QKeySequence &value);
	void slotSetValue(const QKeySequence &value);
};

// QtCharEdit

class QtCharEdit : public QWidget
{
	Q_OBJECT
public:
	QtCharEdit(QWidget *parent = 0);

	QChar value() const;
	bool eventFilter(QObject *o, QEvent *e);
	public Q_SLOTS:
		void setValue(const QChar &value);
Q_SIGNALS:
		void valueChanged(const QChar &value);
protected:
	void focusInEvent(QFocusEvent *e);
	void focusOutEvent(QFocusEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void paintEvent(QPaintEvent *);
	bool event(QEvent *e);
	private slots:
		void slotClearChar();
private:
	void handleKeyEvent(QKeyEvent *e);

	QChar m_value;
	QLineEdit *m_lineEdit;
};

// QtCharEditorFactory
class QtCharEditorFactory;
class QtCharEditorFactoryPrivate : public EditorFactoryPrivate<QtCharEdit>
{
	QtCharEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtCharEditorFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QChar &value);
	void slotSetValue(const QChar &value);

};

// QtEnumEditorFactory
class QtEnumEditorFactory;
class QtEnumEditorFactoryPrivate : public EditorFactoryPrivate<QComboBox>
{
	QtEnumEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtEnumEditorFactory)
public:

	void slotPropertyChanged(QtProperty *property, int value);
	void slotEnumNamesChanged(QtProperty *property, const QStringList &);
	void slotEnumIconsChanged(QtProperty *property, const QMap<int, QIcon> &);
	void slotSetValue(int value);
};


// QtColorEditWidget

class QtColorEditWidget : public QWidget {
	Q_OBJECT

public:
	QtColorEditWidget(QWidget *parent);

	bool eventFilter(QObject *obj, QEvent *ev);

	public Q_SLOTS:
		void setValue(const QColor &value);

Q_SIGNALS:
		void valueChanged(const QColor &value);

protected:
	void paintEvent(QPaintEvent *);

	private Q_SLOTS:
		void buttonClicked();

private:
	QColor m_color;
	QLabel *m_pixmapLabel;
	QLabel *m_label;
	QToolButton *m_button;
};


// QtFontEditWidget

class QtFontEditWidget : public QWidget {
	Q_OBJECT

public:
	QtFontEditWidget(QWidget *parent);

	bool eventFilter(QObject *obj, QEvent *ev);

	public Q_SLOTS:
		void setValue(const QFont &value);

Q_SIGNALS:
		void valueChanged(const QFont &value);

protected:
	void paintEvent(QPaintEvent *);

	private Q_SLOTS:
		void buttonClicked();

private:
	QFont m_font;
	QLabel *m_pixmapLabel;
	QLabel *m_label;
	QToolButton *m_button;
};


// QtCursorEditorFactory
class QtCursorEditorFactory; 
class QtEnumPropertyManager;

Q_GLOBAL_STATIC(QtCursorDatabase, cursorDatabase)

class QtCursorEditorFactoryPrivate
{
	QtCursorEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtCursorEditorFactory)
public:
	QtCursorEditorFactoryPrivate();

	void slotPropertyChanged(QtProperty *property, const QCursor &cursor);
	void slotEnumChanged(QtProperty *property, int value);
	void slotEditorDestroyed(QObject *object);

	QtEnumEditorFactory *m_enumEditorFactory;
	QtEnumPropertyManager *m_enumPropertyManager;

	QMap<QtProperty *, QtProperty *> m_propertyToEnum;
	QMap<QtProperty *, QtProperty *> m_enumToProperty;
	QMap<QtProperty *, QList<QWidget *> > m_enumToEditors;
	QMap<QWidget *, QtProperty *> m_editorToEnum;
	bool m_updatingEnum;
};

// QtColorEditorFactoryPrivate
class QtColorEditorFactory;
class QtColorEditorFactoryPrivate : public EditorFactoryPrivate<QtColorEditWidget>
{
	QtColorEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtColorEditorFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QColor &value);
	void slotSetValue(const QColor &value);
};

// QtFontEditorFactoryPrivate
class QtFontEditorFactory;
class QtFontEditorFactoryPrivate : public EditorFactoryPrivate<QtFontEditWidget>
{
	QtFontEditorFactory *q_ptr;
	Q_DECLARE_PUBLIC(QtFontEditorFactory)
public:

	void slotPropertyChanged(QtProperty *property, const QFont &value);
	void slotSetValue(const QFont &value);
};

// QtLocalePropertyManager
class QtLocalePropertyManager;

class QtLocalePropertyManagerPrivate
{
	QtLocalePropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtLocalePropertyManager)
public:

	QtLocalePropertyManagerPrivate();

	void slotEnumChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);

	typedef QMap<const QtProperty *, QLocale> PropertyValueMap;
	PropertyValueMap m_values;

	QtEnumPropertyManager *m_enumPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToLanguage;
	QMap<const QtProperty *, QtProperty *> m_propertyToCountry;

	QMap<const QtProperty *, QtProperty *> m_languageToProperty;
	QMap<const QtProperty *, QtProperty *> m_countryToProperty;
};

// QtPointPropertyManager
class QtPointPropertyManager;

class QtPointPropertyManagerPrivate
{
	QtPointPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtPointPropertyManager)
public:

	void slotIntChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);

	typedef QMap<const QtProperty *, QPoint> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToX;
	QMap<const QtProperty *, QtProperty *> m_propertyToY;

	QMap<const QtProperty *, QtProperty *> m_xToProperty;
	QMap<const QtProperty *, QtProperty *> m_yToProperty;
};

// QtPointFPropertyManager
class QtPointFPropertyManager;
class QtDoublePropertyManager;

class QtPointFPropertyManagerPrivate
{
	QtPointFPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtPointFPropertyManager)
public:

	struct Data
	{
		Data() : decimals(2) {}
		QPointF val;
		int decimals;
	};

	void slotDoubleChanged(QtProperty *property, double value);
	void slotPropertyDestroyed(QtProperty *property);

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtDoublePropertyManager *m_doublePropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToX;
	QMap<const QtProperty *, QtProperty *> m_propertyToY;

	QMap<const QtProperty *, QtProperty *> m_xToProperty;
	QMap<const QtProperty *, QtProperty *> m_yToProperty;
};

// QtSizePropertyManager
class QtSizePropertyManager;
class QtSizePropertyManagerPrivate
{
	QtSizePropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtSizePropertyManager)
public:

	void slotIntChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);
	void setValue(QtProperty *property, const QSize &val);
	void setRange(QtProperty *property,
		const QSize &minVal, const QSize &maxVal, const QSize &val);

	struct Data
	{
		Data() : val(QSize(0, 0)), minVal(QSize(0, 0)), maxVal(QSize(INT_MAX, INT_MAX)) {}
		QSize val;
		QSize minVal;
		QSize maxVal;
		QSize minimumValue() const { return minVal; }
		QSize maximumValue() const { return maxVal; }
		void setMinimumValue(const QSize &newMinVal) { setSizeMinimumData(this, newMinVal); }
		void setMaximumValue(const QSize &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
	};

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToW;
	QMap<const QtProperty *, QtProperty *> m_propertyToH;

	QMap<const QtProperty *, QtProperty *> m_wToProperty;
	QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

// QtSizeFPropertyManager
class QtSizeFPropertyManager;

class QtSizeFPropertyManagerPrivate
{
	QtSizeFPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtSizeFPropertyManager)
public:

	void slotDoubleChanged(QtProperty *property, double value);
	void slotPropertyDestroyed(QtProperty *property);
	void setValue(QtProperty *property, const QSizeF &val);
	void setRange(QtProperty *property,
		const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val);

	struct Data
	{
		Data() : val(QSizeF(0, 0)), minVal(QSizeF(0, 0)), maxVal(QSizeF(INT_MAX, INT_MAX)), decimals(2) {}
		QSizeF val;
		QSizeF minVal;
		QSizeF maxVal;
		int decimals;
		QSizeF minimumValue() const { return minVal; }
		QSizeF maximumValue() const { return maxVal; }
		void setMinimumValue(const QSizeF &newMinVal) { setSizeMinimumData(this, newMinVal); }
		void setMaximumValue(const QSizeF &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
	};

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtDoublePropertyManager *m_doublePropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToW;
	QMap<const QtProperty *, QtProperty *> m_propertyToH;

	QMap<const QtProperty *, QtProperty *> m_wToProperty;
	QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

// QtRectPropertyManager
class QtRectPropertyManager;
class QtRectPropertyManagerPrivate
{
	QtRectPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtRectPropertyManager)
public:

	void slotIntChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);
	void setConstraint(QtProperty *property, const QRect &constraint, const QRect &val);

	struct Data
	{
		Data() : val(0, 0, 0, 0) {}
		QRect val;
		QRect constraint;
	};

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToX;
	QMap<const QtProperty *, QtProperty *> m_propertyToY;
	QMap<const QtProperty *, QtProperty *> m_propertyToW;
	QMap<const QtProperty *, QtProperty *> m_propertyToH;

	QMap<const QtProperty *, QtProperty *> m_xToProperty;
	QMap<const QtProperty *, QtProperty *> m_yToProperty;
	QMap<const QtProperty *, QtProperty *> m_wToProperty;
	QMap<const QtProperty *, QtProperty *> m_hToProperty;
};


// QtRectFPropertyManager
class QtRectFPropertyManager;
class QtRectFPropertyManagerPrivate
{
	QtRectFPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtRectFPropertyManager)
public:

	void slotDoubleChanged(QtProperty *property, double value);
	void slotPropertyDestroyed(QtProperty *property);
	void setConstraint(QtProperty *property, const QRectF &constraint, const QRectF &val);

	struct Data
	{
		Data() : val(0, 0, 0, 0), decimals(2) {}
		QRectF val;
		QRectF constraint;
		int decimals;
	};

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtDoublePropertyManager *m_doublePropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToX;
	QMap<const QtProperty *, QtProperty *> m_propertyToY;
	QMap<const QtProperty *, QtProperty *> m_propertyToW;
	QMap<const QtProperty *, QtProperty *> m_propertyToH;

	QMap<const QtProperty *, QtProperty *> m_xToProperty;
	QMap<const QtProperty *, QtProperty *> m_yToProperty;
	QMap<const QtProperty *, QtProperty *> m_wToProperty;
	QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

// QtFlagPropertyManager
class QtFlagPropertyManager;
class QtBoolPropertyManager;

class QtFlagPropertyManagerPrivate
{
	QtFlagPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtFlagPropertyManager)
public:

	void slotBoolChanged(QtProperty *property, bool value);
	void slotPropertyDestroyed(QtProperty *property);

	struct Data
	{
		Data() : val(-1) {}
		int val;
		QStringList flagNames;
	};

	typedef QMap<const QtProperty *, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtBoolPropertyManager *m_boolPropertyManager;

	QMap<const QtProperty *, QList<QtProperty *> > m_propertyToFlags;

	QMap<const QtProperty *, QtProperty *> m_flagToProperty;
};


// QtSizePolicyPropertyManager
class QtSizePolicyPropertyManager;

class QtSizePolicyPropertyManagerPrivate
{
	QtSizePolicyPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtSizePolicyPropertyManager)
public:

	QtSizePolicyPropertyManagerPrivate();

	void slotIntChanged(QtProperty *property, int value);
	void slotEnumChanged(QtProperty *property, int value);
	void slotPropertyDestroyed(QtProperty *property);

	typedef QMap<const QtProperty *, QSizePolicy> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;
	QtEnumPropertyManager *m_enumPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToHPolicy;
	QMap<const QtProperty *, QtProperty *> m_propertyToVPolicy;
	QMap<const QtProperty *, QtProperty *> m_propertyToHStretch;
	QMap<const QtProperty *, QtProperty *> m_propertyToVStretch;

	QMap<const QtProperty *, QtProperty *> m_hPolicyToProperty;
	QMap<const QtProperty *, QtProperty *> m_vPolicyToProperty;
	QMap<const QtProperty *, QtProperty *> m_hStretchToProperty;
	QMap<const QtProperty *, QtProperty *> m_vStretchToProperty;
};



// QtFontPropertyManager:
// QtFontPropertyManagerPrivate has a mechanism for reacting
// to QApplication::fontDatabaseChanged() [4.5], which is emitted
// when someone loads an application font. The signals are compressed
// using a timer with interval 0, which then causes the family
// enumeration manager to re-set its strings and index values
// for each property.

class QtFontPropertyManager;

Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)


class QtFontPropertyManagerPrivate
{
	QtFontPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtFontPropertyManager)
public:

	QtFontPropertyManagerPrivate();

	void slotIntChanged(QtProperty *property, int value);
	void slotEnumChanged(QtProperty *property, int value);
	void slotBoolChanged(QtProperty *property, bool value);
	void slotPropertyDestroyed(QtProperty *property);
	void slotFontDatabaseChanged();
	void slotFontDatabaseDelayedChange();

	QStringList m_familyNames;

	typedef QMap<const QtProperty *, QFont> PropertyValueMap;
	PropertyValueMap m_values;

	QtIntPropertyManager *m_intPropertyManager;
	QtEnumPropertyManager *m_enumPropertyManager;
	QtBoolPropertyManager *m_boolPropertyManager;

	QMap<const QtProperty *, QtProperty *> m_propertyToFamily;
	QMap<const QtProperty *, QtProperty *> m_propertyToPointSize;
	QMap<const QtProperty *, QtProperty *> m_propertyToBold;
	QMap<const QtProperty *, QtProperty *> m_propertyToItalic;
	QMap<const QtProperty *, QtProperty *> m_propertyToUnderline;
	QMap<const QtProperty *, QtProperty *> m_propertyToStrikeOut;
	QMap<const QtProperty *, QtProperty *> m_propertyToKerning;

	QMap<const QtProperty *, QtProperty *> m_familyToProperty;
	QMap<const QtProperty *, QtProperty *> m_pointSizeToProperty;
	QMap<const QtProperty *, QtProperty *> m_boldToProperty;
	QMap<const QtProperty *, QtProperty *> m_italicToProperty;
	QMap<const QtProperty *, QtProperty *> m_underlineToProperty;
	QMap<const QtProperty *, QtProperty *> m_strikeOutToProperty;
	QMap<const QtProperty *, QtProperty *> m_kerningToProperty;

	bool m_settingValue;
	QTimer *m_fontDatabaseChangeTimer;
};

// QtCursorPropertyManager
class QtCursorPropertyManager;

//Q_GLOBAL_STATIC(QtCursorDatabase, cursorDatabase)

class QtCursorPropertyManagerPrivate
{
	QtCursorPropertyManager *q_ptr;
	Q_DECLARE_PUBLIC(QtCursorPropertyManager)
public:
	typedef QMap<const QtProperty *, QCursor> PropertyValueMap;
	PropertyValueMap m_values;
};

#endif // QTFACTORYPRIVATE_H