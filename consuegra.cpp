#include "consuegra.h"
consuegra::consuegra(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connects();
}

consuegra::~consuegra()
{

}

void consuegra::connects()
{
	connect(ui.import_cv, SIGNAL(triggered()), this, SLOT(import()));
}

void consuegra::import()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		QDir::currentPath(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty())
	{
		QMessageBox q;
		q.setText("null");
		q.show();
	}
	qDebug("%s", dir);

	find(dir);

	QStandardItemModel *model = new QStandardItemModel(2,3,this); //2 Rows and 3 Columns
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

	ui.tableView->setModel(model);
}

QStringList consuegra::findFilesRecursively (QProgressDialog &progressDialog, QStringList &paths, QString fileTypes ) {
	if ( fileTypes.isEmpty() ) fileTypes = "*";
	QStringList result, more;
	QStringList::Iterator it;
	for ( uint i = 0 ; i < paths.size() ; i++ ) { // inefficient...whatever
		QDir dir( paths[i] );
		more = dir.entryList( QStringList(fileTypes), QDir::Files );
		qDebug("Matching file number %d in %s ...", more.size(), paths[i]);
		progressDialog.setLabelText(tr("Matching file number %1 ...").arg(more.size()));
		// reg exp in next line excludes . and .. dirs (and .* actually)
		more = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		more = findFilesRecursively(progressDialog, more, fileTypes );
	}
	return result; // yields absolute paths
}

void consuegra::find(const QString &path)
{
	QDir currentDir = QDir(path);
	QStringList files;
	files = currentDir.entryList(QStringList("*"),
		QDir::Files | QDir::NoSymLinks);
	QString text = "*.doc";

	

	QProgressDialog progressDialog(this);
	progressDialog.setCancelButtonText(tr("&Cancel"));
	progressDialog.setRange(0, files.size());
	progressDialog.setWindowTitle(tr("Find Files"));
	progressDialog.show();


	qDebug("%s", path);
	QStringList foundFiles = findFilesRecursively(progressDialog, QStringList(path), text);

	//for (int i = 0; i < files.size(); ++i) {
	//	progressDialog.setLabelText(tr("Searching file number %1 of %2...").arg(i).arg(files.size()));
	//	qApp->processEvents();
	//	QFile file(currentDir.absoluteFilePath(files[i]));

	//	if (file.open(QIODevice::ReadOnly)) {
	//		QString line;
	//		QTextStream in(&file);
	//		while (!in.atEnd()) {
	//			if (progressDialog.wasCanceled())
	//				break;
	//			line = in.readLine();
	//			if (line.contains(text)) {
	//				foundFiles << files[i];
	//				break;
	//			}
	//		}
	//	}
	//}
}
