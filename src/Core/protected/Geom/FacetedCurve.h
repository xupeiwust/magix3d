/*----------------------------------------------------------------------------*/
/*
 * \file FacetedCurve.h
 *
 *  \author Eric Brière de l'Isle
 *
 *  \date 27 févr. 2018
 */
/*----------------------------------------------------------------------------*/
#ifndef MGX3D_GEOM_FACETEDCURVE_H_
#define MGX3D_GEOM_FACETEDCURVE_H_
/*----------------------------------------------------------------------------*/
#include "Geom/GeomRepresentation.h"
#include "Internal/Context.h"
/*----------------------------------------------------------------------------*/

#include <gmds/ig/Node.h>

#include <gts.h>
/*----------------------------------------------------------------------------*/
namespace Mgx3D {
/*----------------------------------------------------------------------------*/
namespace Geom {
/*----------------------------------------------------------------------------*/
class FacetedVertex;
/*----------------------------------------------------------------------------*/

/**
 * \class FacetedCurve
 *
 * \brief Propriétés géométriques d'un objet curviligne facétisé (nuage de noeuds)
 */
class FacetedCurve: public GeomRepresentation{

public:

    /*------------------------------------------------------------------------*/
    /** \brief  Constructeur avec un ensemble ordonné de noeuds
     *                                        -------
     */
	FacetedCurve(Internal::Context& c, uint gmds_id, std::vector<gmds::Node>& nodes);

	/*------------------------------------------------------------------------*/
	/** \brief  Constructeur par copie
	 */
	FacetedCurve(const FacetedCurve& rep);

	/*------------------------------------------------------------------------*/
	/** \brief  Destructeur
	 */
	virtual ~FacetedCurve();

    /*------------------------------------------------------------------------*/
    /** \brief  Fournit un clone de l'instance de représentation géométrique.
     *          Pour cela, un appel à "new" est effectué dans cette commande.
     *
     *  \return un pointeur vers une représentation géométrique identique
     */
    GeomRepresentation* clone() const;

    /*------------------------------------------------------------------------*/
    /** \brief  Calcule l'aire d'une entité. Aucun sens pour un sommet.
     */
    double computeVolumeArea();
    double computeSurfaceArea();
    double computeCurveArea();

    /*------------------------------------------------------------------------*/
    /** \brief  Calcul de la boite englobante orientée selon les axes Ox,Oy,Oz
     *
     *  \param pmin Les coordonnées min de la boite englobante
     *  \param pmax Les coordonnées max de la boite englobante
     */
    void computeBoundingBox(Utils::Math::Point& pmin,Utils::Math::Point& pmax, double tol) const;

    /*------------------------------------------------------------------------*/
    /** \brief  Décompose l'entité volumique en ses sous-entités. Aucun sens
     *          pour un sommet.
     */
    void split(std::vector<Surface* >& surf,
               std::vector<Curve*>& curv,
               std::vector<Vertex* >&  vert,
               Volume* owner);

    /*------------------------------------------------------------------------*/
    /** \brief  Décompose l'entité surfacique en ses sous-entités. Aucun sens
     *          pour un sommet.
     */
    void split(std::vector<Curve*>& curv,
               std::vector<Vertex* >&  vert,
               Surface* owner);

    /*------------------------------------------------------------------------*/
    /** \brief  Décompose l'entité linéaire en ses sous-entités. Aucun sens
     *          pour un sommet.
     */
    void split( std::vector<Vertex* >&  vert,
                Curve* owner);

    /*------------------------------------------------------------------------*/
    /** \brief Projete le point P sur l'entité géométrique associée.
     *
     *  \param P le point à projeter qui sera modifié
     *  \param C la courbe sur laquelle on projette
     */
    void project( Utils::Math::Point& P, const Curve* C);

    /*------------------------------------------------------------------------*/
    /** \brief Projete le point P sur l'entité géométrique associée.
     *
     *  \param P le point à projeter qui sera modifié
     *  \param S la surface sur laquelle on projette
     */
    void project( Utils::Math::Point& P, const Surface* S);

    /*------------------------------------------------------------------------*/
    /** \brief Projete le point P1 sur l'entité géométrique associée.
     *         Le résultat est le point P2.
     *
     *  \param P1 le point à projeter
     *  \param P2 le résultat de la projection
     *  \param S la surface sur laquelle on projete
     */
    void project(const Utils::Math::Point& P1, Utils::Math::Point& P2, const Surface* S);

    /*------------------------------------------------------------------------*/
    /** \brief Projete le point P1 sur l'entité géométrique associée.
     *         Le résultat est le point P2.
     *
     *  \param P1 le point à projeter
     *  \param P2 le résultat de la projection
     *  \param C la courbe sur laquelle on projete
     */
    void project(const Utils::Math::Point& P1, Utils::Math::Point& P2, const Curve* C);

    /*------------------------------------------------------------------------*/
    /** \brief Calcul la normale à une surface en un point
     *
     *  \param P1 le point à projeter
     *  \param V2 la normale recherchée suivant le projeté du point
     *  \param S la surface sur laquelle on projete
     */
    void normal(const Utils::Math::Point& P1, Utils::Math::Vector& V2, const Surface* S);

    /*------------------------------------------------------------------------*/
    /** \brief Donne le point en fonction du paramètre pour une courbe
     * \param p le paramètre curviligne
     * \param Pt le résultat
     */
    void getPoint(const double& p, Utils::Math::Point& Pt,
            const bool in01=false);

    /*------------------------------------------------------------------------*/
    /** \brief Donne le point a l'intersection avec le plan
     * \param plan_cut le plan
     * \param Pt le résultat
     */
    void getIntersection(gp_Pln& plan_cut, Utils::Math::Point& Pt);

    /*------------------------------------------------------------------------*/
    /** \brief Donne le paramètre curviligne du point pour une courbe
     * \param Pt le point sur la courbe
     */
    void getParameter(const Utils::Math::Point& Pt, double& p, const Curve* C);

    /*------------------------------------------------------------------------*/
    /** \brief Donne les paramètres curviligne aux extrémités de la courbe
     */
    void getParameters(double& first, double& last);

    /*------------------------------------------------------------------------*/
    /** \brief Effectue la translation de l'entité géométrique associée de
     *         manière isolée. C'est-à-dire que aucune des entités incidentes
     *         n'est impactée par ce traitement
     *
     *  \param V le vecteur de translation à appliquer
     */
    void translate(const Utils::Math::Vector& V);
    /*------------------------------------------------------------------------*/
    /** \brief Effectue l'homothétié de l'entité géométrique associée de
     *         manière isolée. C'est-à-dire que aucune des entités incidentes
     *         n'est impactée par ce traitement
     *
     *  \param F le facteur d'homothétie
     *  \param center le centre d'homothétie
     */
    void scale(const double F, const Utils::Math::Point& center);
    void scale(const double factorX,
                const double factorY,
                const double factorZ,
                const Utils::Math::Point& center);

    /*------------------------------------------------------------------------*/
    /** \brief Effectue la rotation de l'entité géométrique associée de
     *         manière isolée. C'est-à-dire que aucune des entités incidentes
     *         n'est impactée par ce traitement
     *
     *  \param P1    premier point definissant l'axe de rotation
     *  \param P2    second point definissant l'axe de rotation
     *  \param Angle    angle de rotation en degré (compris entre ]0,360])
     */
    void rotate(const Utils::Math::Point& P1,
            const Utils::Math::Point& P2, double Angle);

    /*------------------------------------------------------------------------*/
    /** \brief Effectue la symétrie de l'entité géométrique associée de
     *         manière isolée. C'est-à-dire que aucune des entités incidentes
     *         n'est impactée par ce traitement
     *
     *  \param plane le plan de symétrie
     */
    void mirror(const Utils::Math::Plane& plane);

    /*------------------------------------------------------------------------*/
    /** \brief  Fournit une représentation affichable de l'entité en se basant
     *          sur la représentation passée en paramètre
     *
     *  \param dr la représentation que l'on demande à afficher
     *  \param caller un pointeur sur la géométrie appelant cette méthode. Il
     *         est nécessaire à cause de la discrétisation de courbes qui
     *         peuvent nécessiter d'accéder à des entités de dimension
     *         supérieure.
     */
    void buildDisplayRepresentation(Utils::DisplayRepresentation& dr,
                                    const GeomEntity* caller) const;

    /*------------------------------------------------------------------------*/
    /** \brief  Fournit une représentation facétisée (point, segments, polygones) de l'entité
     *
     */
    virtual void getFacetedRepresentation(
            std::vector<gmds::math::Triangle >& AVec,
            const GeomEntity* caller) const;

    /*------------------------------------------------------------------------*/
    /** \brief  Renvoie si la surface AEntityOrientation est bien orientée
     * 			par rapport au volume ACaller.
     *
     */
    virtual void facetedRepresentationForwardOrient(
    		const GeomEntity* ACaller,
    		const GeomEntity* AEntityOrientation,
    		std::vector<gmds::math::Triangle>*) const;

    /*------------------------------------------------------------------------*/
    /** \brief Calcul la tangente à une courbe en un point
     *
     *  \param P1 le point à projeter
     *  \param V2 la tangente recherchée suivant le projeté du point
     *  \param C la courbe sur laquelle on projete
     */
    virtual void tangent(const Utils::Math::Point& P1, Utils::Math::Vector& V2);


    /*------------------------------------------------------------------------*/
    /** \brief  Fournit la précision
     *
     *  \return un double (en général de l'ordre de e-5)
     */
    virtual double getPrecision();

    /*------------------------------------------------------------------------*/
    /** \brief  Retourne le nombre de noeuds
     */
    virtual uint getNbNodes() const {return m_nodes.size();}

    /*------------------------------------------------------------------------*/
    /** \brief  Retourne les noeuds
     */
    virtual const std::vector<gmds::Node>& getNodes() const {return m_nodes;}

    /*------------------------------------------------------------------------*/
    /** \brief  retourne l'indice du noeud le plus proche de pt
     * \param pt le point près duquel est coupé la courbe
     */
    virtual size_t getNodeIdNear(const Utils::Math::Point& pt);

    /// accès à l'id du maillage GMDS
    uint getGMDSID() const {return m_gmds_id;}
    void setGMDSID(uint id) {m_gmds_id = id;}

    /// accès aux noeuds de la courbe
    std::vector<gmds::Node>& getGMDSNodes() {return m_nodes;}

private:

    /// recalcul les m_lengths et m_length
    void updateLength();

    /*------------------------------------------------------------------------*/
    /** \brief
     *
     *  \param Pt le point à projeter
     *  \param PtProj le point une fois projeté
     *  \param length la longueur paramétrique du point après projection
     */
    void projectAndParam(const Utils::Math::Point& Pt, Utils::Math::Point& PtProj, double& length);

protected:

    Internal::Context & m_context;

    /// id sur le maillage gmds
    uint m_gmds_id;

    /// Liste des noeuds (gmds) associés
    std::vector<gmds::Node> m_nodes;

    /// Longueur au noeud de départ pour chacun des noeuds
    std::vector<double> m_lengths;

    /// longueur de la courbe (pour éviter de recalculer souvent)
    double m_length;

};
/*----------------------------------------------------------------------------*/
} // end namespace Geom
/*----------------------------------------------------------------------------*/
} // end namespace Mgx3D
/*----------------------------------------------------------------------------*/
#endif /* MGX3D_GEOM_FACETEDCURVE_H_ */
/*----------------------------------------------------------------------------*/
