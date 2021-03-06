/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/geometry/qgsgeometrycollection.h                            *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/






class QgsGeometryCollection: QgsAbstractGeometry
{
%Docstring
 Geometry collection

.. versionadded:: 2.10
%End

%TypeHeaderCode
#include "qgsgeometrycollection.h"
%End
  public:
    QgsGeometryCollection();
    QgsGeometryCollection( const QgsGeometryCollection &c );
    ~QgsGeometryCollection();

    virtual bool operator==( const QgsAbstractGeometry &other ) const;

    virtual bool operator!=( const QgsAbstractGeometry &other ) const;


    virtual QgsGeometryCollection *clone() const /Factory/;


    int numGeometries() const;
%Docstring
Returns the number of geometries within the collection.
%End


    QgsAbstractGeometry *geometryN( int n );
%Docstring
Returns a geometry from within the collection.

:param n: index of geometry to return
%End

    virtual bool isEmpty() const;

    virtual int dimension() const;

    virtual QString geometryType() const;

    virtual void clear();

    virtual QgsGeometryCollection *snappedToGrid( double hSpacing, double vSpacing, double dSpacing = 0, double mSpacing = 0 ) const /Factory/;

    virtual bool removeDuplicateNodes( double epsilon = 4 * DBL_EPSILON, bool useZValues = false );

    virtual QgsAbstractGeometry *boundary() const /Factory/;

    virtual void adjacentVertices( QgsVertexId vertex, QgsVertexId &previousVertex /Out/, QgsVertexId &nextVertex /Out/ ) const;

    virtual int vertexNumberFromVertexId( QgsVertexId id ) const;


    virtual bool addGeometry( QgsAbstractGeometry *g /Transfer/ );
%Docstring
Adds a geometry and takes ownership. Returns true in case of success.
%End

    virtual bool insertGeometry( QgsAbstractGeometry *g /Transfer/, int index );
%Docstring
Inserts a geometry before a specified index and takes ownership. Returns true in case of success.

:param g: geometry to insert. Ownership is transferred to the collection.
:param index: position to insert geometry before
%End

    virtual bool removeGeometry( int nr );
%Docstring
Removes a geometry from the collection.

:param nr: index of geometry to remove

:return: true if removal was successful.
%End

     virtual void transform( const QgsCoordinateTransform &ct, QgsCoordinateTransform::TransformDirection d = QgsCoordinateTransform::ForwardTransform,
                    bool transformZ = false );
    virtual void transform( const QTransform &t, double zTranslate = 0.0, double zScale = 1.0, double mTranslate = 0.0, double mScale = 1.0 );


    virtual void draw( QPainter &p ) const;


    virtual bool fromWkb( QgsConstWkbPtr &wkb );

    virtual bool fromWkt( const QString &wkt );

    virtual QByteArray asWkb() const;

    virtual QString asWkt( int precision = 17 ) const;

    virtual QDomElement asGml2( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const;

    virtual QDomElement asGml3( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const;

    virtual QString asJson( int precision = 17 ) const;


    virtual QgsRectangle boundingBox() const;


    virtual QgsCoordinateSequence coordinateSequence() const;

    virtual int nCoordinates() const;


    virtual double closestSegment( const QgsPoint &pt, QgsPoint &segmentPt /Out/, QgsVertexId &vertexAfter /Out/, int *leftOf /Out/ = 0, double epsilon = 4 * DBL_EPSILON ) const;

    virtual bool nextVertex( QgsVertexId &id, QgsPoint &vertex /Out/ ) const;


    virtual bool insertVertex( QgsVertexId position, const QgsPoint &vertex );

    virtual bool moveVertex( QgsVertexId position, const QgsPoint &newPos );

    virtual bool deleteVertex( QgsVertexId position );


    virtual double length() const;

    virtual double area() const;

    virtual double perimeter() const;


    virtual bool hasCurvedSegments() const;


    virtual QgsAbstractGeometry *segmentize( double tolerance = M_PI_2 / 90, SegmentationToleranceType toleranceType = MaximumAngle ) const /Factory/;

%Docstring
Returns a geometry without curves. Caller takes ownership

:param tolerance: segmentation tolerance
:param toleranceType: maximum segmentation angle or maximum difference between approximation and curve*
%End

    virtual double vertexAngle( QgsVertexId vertex ) const;

    virtual double segmentLength( QgsVertexId startVertex ) const;

    virtual int vertexCount( int part = 0, int ring = 0 ) const;

    virtual int ringCount( int part = 0 ) const;

    virtual int partCount() const;

    virtual QgsPoint vertexAt( QgsVertexId id ) const;


    virtual bool addZValue( double zValue = 0 );

    virtual bool addMValue( double mValue = 0 );

    virtual bool dropZValue();

    virtual bool dropMValue();

    virtual QgsGeometryCollection *toCurveType() const /Factory/;



  protected:
    virtual QgsGeometryCollection *createEmptyWithSameType() const /Factory/;

    virtual int childCount() const;

    virtual QgsAbstractGeometry *childGeometry( int index ) const;


  protected:

    virtual bool wktOmitChildType() const;
%Docstring
Returns whether child type names are omitted from Wkt representations of the collection

.. versionadded:: 2.12
%End

    bool fromCollectionWkt( const QString &wkt, const QVector<QgsAbstractGeometry *> &subtypes, const QString &defaultChildWkbType = QString() );
%Docstring
Reads a collection from a WKT string.
%End

    virtual QgsRectangle calculateBoundingBox() const;

    virtual void clearCache() const;


};


/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/geometry/qgsgeometrycollection.h                            *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
