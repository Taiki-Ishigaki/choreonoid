#ifndef CNOID_BODY_JOINT_TRAVERSE_H
#define CNOID_BODY_JOINT_TRAVERSE_H

#include "LinkTraverse.h"
#include "exportdecl.h"

namespace cnoid {

class CNOID_EXPORT JointTraverse
{
public:
    JointTraverse();
    //! This constructor sets the default joint traverse of the body
    JointTraverse(Body* body);
    JointTraverse(const JointTraverse& org);

    void clear();
    bool empty() const { return linkTraverse_.empty() && joints_.empty(); }

    Body* body() { return joints_.empty() ? joints_.front()->body() : nullptr; }

    LinkTraverse& linkTraverse() { return linkTraverse_; }
    const LinkTraverse& linkTraverse() const { return linkTraverse_; }

    void appendLink(Link* link, bool isDownward = true) {
        linkTraverse_.append(link, isDownward);
    }
    int numLinks() const {
        return linkTraverse_.numLinks();
    }
    Link* link(int index) const {
        return linkTraverse_.link(index);
    }

    bool appendJoint(Link* joint);
    int numJoints() const {
        return static_cast<int>(joints_.size());
    }
    Link* joint(int index) const {
        return joints_[index];
    }

    //! This function removes the link from both the link traverse and the joint array
    bool remove(Link* link);

    typedef std::vector<LinkPtr>::iterator iterator;
    typedef std::vector<LinkPtr>::const_iterator const_iterator;

    iterator begin() { return joints_.begin(); }
    iterator end() { return joints_.end(); }
    const_iterator begin() const { return joints_.begin(); }
    const_iterator end() const { return joints_.end(); }
	
    void calcForwardKinematics(bool calcVelocity = false, bool calcAcceleration = false) const {
        linkTraverse_.calcForwardKinematics(calcVelocity, calcAcceleration);
    }

private:
    std::vector<LinkPtr> joints_;
    LinkTraverse linkTraverse_;
};

}
    
#endif
